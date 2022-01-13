<div id="top"></div>
<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->

<!-- TABLE OF CONTENTS -->
<!--<details>-->
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
<!--</details>-->



<!-- ABOUT THE PROJECT -->
## About The Project

<!--[![Product Name Screen Shot][product-screenshot]](https://example.com)-->

This repository shows how a F1 2021 Header is done. The goal is to have a screen header on my gaming wheel to get the most useful information directly on the screen, without having to get through pages in the game.
The project is hardware based on ESP8266. I chose this platform because it already had built-in WiFi stack and is very easy to use. The demo board is tiny and can be easily integrated in a box printed with a 3D printer.
The screen is a LCD screen coming directly from China. It communicates through a SPI serial communication. 
The goal of the software architecture is to separate all the functions to get less independant functional blocks possible. For example, the UDP parser can be used by someone else on another project.
The project is made with the following blocks:
* Low level drivers:
  * WiFiDriver: Connects to a WiFi hotspot, starts a UDP client and receive UDP raw packets
  * LogDriver: Logs string data for debug purposes
  * LCDDriver: Drives the LCD screen
* Middleware drivers:
  * UDP_Parser: Gets UDP raw packets and decodes the packets to fill the data structures given by the F1 UDP specification
  * ScreenHandler: Draws and writes data on the LCD screen
* Application:
  * Telemetry_Messages: Read data from UDP_Parser and sorts them to get only why I judge interresting variables
  * F1_Telemetry: Handles all the functional blocks

<p align="right">(<a href="#top">back to top</a>)</p>

### Built With

Project is build using [PlatformIO](https://platformio.org/). This platform has an addon on [Visual Studio Code](https://code.visualstudio.com/) which makes very easy the use of public known microcontrollers. This addon directly handles all frameworks, compiler chain and all this stuff.
The project is coded in C++.

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- ROADMAP -->
## Roadmap

- [x] Connect to WiFi and get raw UDP packets
- [x] Decode UDP packets
- [x] Sort only useful data
- [ ] Drive the LCD screen
- [ ] Make a graphic example to see how the data will be shown
- [ ] Implements the graphic example
- [ ] Link all the functional blocks

See the [open issues](https://github.com/Judicael-Marchand/F1_2021_Header/issues) for a full list of proposed features (and known issues).

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".
Don't forget to give the project a star! Thanks again!

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- LICENSE -->
## License

There's no license, or at least, not yet.

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

Thanks to [armytricks](https://github.com/armytricks/F1TelemetryDevice) who gave me this idea.

Thanks to [othneildrew](https://github.com/othneildrew/Best-README-Template) for the README template.

<p align="right">(<a href="#top">back to top</a>)</p>