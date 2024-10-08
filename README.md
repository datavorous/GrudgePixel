<div align="center">
   
# GrudgePixel
[![Github All Releases](https://img.shields.io/github/downloads/datavorous/GrudgePixel/total.svg)]() 
<a href="https://github.com/datavorous/GrudgePixel/blob/master/LICENSE"><img src="https://img.shields.io/github/license/datavorous/GrudgePixel" alt="License"></a>

</div>

GrudgePixel is a streamlined pixel art editor designed to provide an efficient and user-friendly experience. With its focus on speed, minimalism, and ease of use, GrudgePixel stands out as a top choice for both beginners and experienced pixel artists.

## Showcase

<table style="width:100%; text-align:center;">
  <tr>
    <td><img src="https://raw.githubusercontent.com/datavorous/GrudgePixel/main/demo/cute_.PNG" alt="Dwarf"></td>
    <td><img src="https://raw.githubusercontent.com/datavorous/GrudgePixel/main/demo/blob.PNG" alt="Blob"></td>
    <td><img src="https://raw.githubusercontent.com/datavorous/GrudgePixel/main/demo/girl.PNG" alt="Girl"></td>
  </tr>
  <tr>
    <td><img src="https://raw.githubusercontent.com/datavorous/GrudgePixel/main/demo/frog.PNG" alt="frog"></td>
    <td><img src="https://raw.githubusercontent.com/datavorous/GrudgePixel/main/demo/knight.PNG" alt="knight"></td>
    <td><img src="https://raw.githubusercontent.com/datavorous/GrudgePixel/main/demo/amogus.PNG" alt="amogus"></td>
  </tr>
</table>

## Why GrudgePixel?

**Optimized Performance**: GrudgePixel is engineered for exceptional speed and responsiveness. Unlike many pixel art editors that can be sluggish or bloated, GrudgePixel ensures smooth operation even with complex animations and large canvases.

**Memory Efficiency**: By avoiding unnecessary features and focusing on core functionality, GrudgePixel keeps memory usage low. This allows it to run seamlessly on a variety of systems, including those with limited resources.

**Simplicity & Usability**: GrudgePixel offers an intuitive interface that eliminates the need for extensive training. Its minimalist design helps users focus on their art without being overwhelmed by extraneous tools and options.

**Minimal Bloat**: Many pixel art editors come with a plethora of features that can make them cumbersome. GrudgePixel avoids this by providing only the essential tools needed for pixel art creation, ensuring a faster and more enjoyable user experience.

> [!TIP]
> Don't overthink about what to make or what colours to choose, just start creating!<br>
> Use our [Photo Enhancer](Enhancer_GUI.py) for editing your pixel art! It supports resizing without quality loss, dithering and colour pallete optimizations.

## Download

For more information and to download GrudgePixel, visit this [page](https://datavorous.github.io/GrudgePixel/).

> [!CAUTION]
> This is **NOT** a virus. Check [here](https://www.virustotal.com/gui/file/f9045baa01ebd5227785c104dea1051a42ce1cc2da9b7576ba72b696aaac147b). If your system doesnt allow it, build from source, follow the raylib website. Learn how to [allow](https://github.com/docker/for-win/issues/13335#issuecomment-1483783763) it. [More](https://answers.microsoft.com/en-us/windows/forum/all/windows-defender-flagged-my-c-program-as-trojan/bfad521c-7129-4f63-8c84-98a16f0a50e2) details from Microsoft's forums.

## User Manual

Please check out the manual [here](https://datavorous.github.io/GrudgePixel/#manual).

## Building from Source

GrudgePixel uses the [premake5](https://premake.github.io/) build system to generate project files for various platforms and IDEs. To build GrudgePixel from source, follow these steps:

1. Clone the repository:

```bash
git clone https://github.com/datavorous/GrudgePixel
cd GrudgePixel
```

2. Run the `premake5` script to generate project files for your platform. For example, on Windows, you can generate MinGW Makefiles:

```bash
premake5 gmake2
```

3. Build the project using the generated project files in `build/`. For example, on Windows with MinGW:

```bash
make -C build                 # Builds in debug mode by default
make -C build config=release  # Builds in release mode
```

4. Run the executable:

```bash
./bin/Debug/GrudgePixel
```

To distribute the executable, you need to copy over the `res/` assets folder to the same directory as the executable.

## Contributing

We welcome contributions to improve GrudgePixel!

## License

GrudgePixel is licensed under the GPL 3.0 License. See [LICENSE](LICENSE) for more information.

## Contact

For support or inquiries, please create an issue or [email](river.shallow631@passinbox.com) me.
