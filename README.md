# What is this?
This project constructs Large-Gap Gray codes (LGGC), which is a special type of Gray code with the additional property that it contains large bit runs along the tracks. LGGC was introduced by [1], where the mathematical derivation of the codes is described. More description of LGGC can be found in [2, section 5.2].

A comparison of *Binary Reflected Gray code* and *Large-Gap Gray code* is shown below:

##### 7-bit Binary Reflected Gray code
![7-bit Binary Reflected Gray code](http://s29.postimg.org/an3fgnj8n/convgraycode7bit.png "7-bit Binary Reflected Gray code")

##### 7-bit Large-Gap Gray code
![7-bit Large-Gap Gray code](http://s11.postimg.org/7p9zzfwcz/graycode7bit_Our.png "7-bit Large-Gap Gray code")

They are both cyclic Gray codes with one bit changing between two successive values, however the LGGC is constructed in a way to obtain higher minimum run lengths and lower maximum run lengths along the bit tracks.

##### Comparison of min/max gaps
![Comparison of min/max gaps for BRGC and LGGC for various bit widths](http://s10.postimg.org/riy04css9/min_max_gap.png)

# Utilization in structured light application
The codes have been used in a structured light application [2]. The LGGC pattern was projected to a scene and captured by cameras. Afterwards, the pattern was decoded and used for reconstruction of 3D information. 

In comparison to traditional BRGC, the properties of LGGC makes it more robust towards defocusing, subsurface scattering and interreflections, which are common challenges in scenes with active illumination. For more information, see [2] and [3].

# How to use it
The project is tested on Linux using CMake and make:
```
mkdir build
cd build
cmake ..
make
```

Two applications are provided, which can be executed by running;
```
./src/examples
./src/imagePatterns
```

# References
* [1] Luis Goddyn, George M Lawrence, and Evi Nemeth. Gray codes with optimized run lengths. Utilitas Mathematica, 34:179–192, 1988
* [2] Pedersen, J. and Hansen, K. (2014). Robot Mountable Embedded Vision Platform for Multimodal Point Cloud Acquisition in Industrial Applications. Master Thesis, University of Southern Denmark. [Online version](http://caro.sdu.dk/index.php/publications/master-theses?view=publication&task=show&id=2048)
* [3] Hansen, K.; Pedersen, J.; Sølund, T.; Aanæs, H.; Kraft, D., "A Structured Light Scanner for Hyper Flexible Industrial Automation", 3D Vision - 3DV 2014
