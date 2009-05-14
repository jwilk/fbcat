#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <linux/fb.h>

#define DEFAULT_FBDEV "/dev/fb0"

void posix_error(const char *s, ...)
{
  va_list argv;
  va_start(argv, s);
  vfprintf(stderr, s, argv);
  fprintf(stderr, ": ");
  perror(NULL);
  va_end(argv);
  exit(2);
}

void not_supported(const char *s)
{
  fprintf(stderr, "Framebuffer device is not supported: %s\n", s);
  exit(3);
}

unsigned char get_color(unsigned int pixel, const struct fb_bitfield *bitfield)
{
  return (pixel >> bitfield->offset) & ((1 << bitfield->length) - 1);
}

void dump_truecolor(const unsigned char *video_memory, const struct fb_var_screeninfo *info, FILE *fp)
{
  unsigned int x, y;
  const size_t bytes_per_pixel = (info->bits_per_pixel + 7) / 8;
  unsigned char *row = malloc(info->xres * 3);
  if (row == NULL)
    posix_error("malloc failed");

  fprintf(fp, "P6 %u %u 255\n", (unsigned int) info->xres, (unsigned int) info->yres); 
  for (y = 0; y < info->yres; y++)
  {
    const unsigned char *current;
    current = video_memory + (info->xoffset + info->xres_virtual * (y + info->yoffset)) * bytes_per_pixel;
    for (x = 0; x < info->xres; x++)
    {
      unsigned int i;
      unsigned int pixel = 0;
      for (i = 0; i < bytes_per_pixel; i++)
      {
        pixel |= current[0] << (i * 8);
        current++;
      }
      row[x * 3 + 0] = get_color(pixel, &info->red);
      row[x * 3 + 1] = get_color(pixel, &info->green);
      row[x * 3 + 2] = get_color(pixel, &info->blue);
    }
    fwrite(row, sizeof(unsigned char), info->xres * 3, fp);
  }

  free(row);
}

int main(int argc, const char **argv)
{
  const char *fbdev_name;
  int fd;

  if (argc > 2 || isatty(STDOUT_FILENO) == 1)
  {
    fprintf(stderr, "Usage: %s [fbdev]\n", argv[0]);
    return 1;
  }

  if (argc == 2)
    fbdev_name = argv[1];
  else
  {
    fbdev_name = getenv("FRAMEBUFFER");
    if (fbdev_name == NULL)
      fbdev_name = DEFAULT_FBDEV;
  }

  fd = open(fbdev_name, O_RDONLY);
  if (fd == -1)
    posix_error("Could not open %s", fbdev_name);

  struct fb_fix_screeninfo fix_info;
  struct fb_var_screeninfo var_info;

  if (ioctl(fd, FBIOGET_FSCREENINFO, &fix_info))
    posix_error("FBIOGET_FSCREENINFO failed");

  if (ioctl(fd, FBIOGET_VSCREENINFO, &var_info))
    posix_error("FBIOGET_VSCREENINFO failed");

  if (fix_info.type != FB_TYPE_PACKED_PIXELS)
    not_supported("framebuffer type is not PACKED_PIXELS");

  const size_t bytes_per_pixel = (var_info.bits_per_pixel + 7) / 8;
  const size_t mapped_length = var_info.xres_virtual * (var_info.yres + var_info.yoffset) * bytes_per_pixel;
  const unsigned char *video_memory;
  video_memory = mmap(NULL, mapped_length, PROT_READ, MAP_SHARED, fd, 0);

  switch (fix_info.visual)
  {
    case FB_VISUAL_TRUECOLOR:
      dump_truecolor(video_memory, &var_info, stdout);
      break;
    default:
      not_supported("unsupported visual");
  }

  close(fd);
  return 0;
}

/* vim:set ts=2 sw=2 et: */
