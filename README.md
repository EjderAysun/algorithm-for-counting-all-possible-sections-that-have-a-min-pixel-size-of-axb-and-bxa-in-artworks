# Algorithm for Counting All Possible Sections that Have a Min Pixel Size of axb and bxa in Artworks 
A simple algorithm to find the number of all possible sections in artworks(or anything rectangular and 2D that can be represented by pixel dimensions) that maintain their styles and don't compromise their essences as long as they have a minimum size of *a*x*b* or *b*x*a* pixels.

---
## Table of Contents
  * [Table of Contents](#table-of-contents)
  * [General Info](#general-info)
  * [Technologies](#technologies)
  * [Setup](#setup)
  * [Features](#features)
  * [Status](#status)
  * [Inspiration](#inspiration)
  * [Version](#version)
  * [Contributors](#contributors)
  * [Licence & Copyright](#licence--copyright)

---
## General Info
$$
\large \underbrace{\displaystyle\sum\limits_{mh = minHeight}^{height} \displaystyle\sum\limits_{mw = minwidth}^{width} (height + 1 - mh)\times(width + 1 - mw)}
$$
<div align="center">
number of all possible sections <ins>for minimum <i>minHeight</i> x <i>minWidth</i> pixel size</ins>
</div>

#### There are 4 variables:
- *height* x *width*
- (*mh*) *minHeight* x *minWidth* (*mw*)

⇒ Let's say *y* = *height* + 1 and *x* = *width* + 1  

$$
\normalsize \displaystyle\sum\limits_{mh = minHeight}^{height} \displaystyle\sum\limits_{mw = minwidth}^{width} (height + 1 - mh)\times(width + 1 - mw)
$$

$$
= (y - mh)\times(x - mw) + (y - mh)\times\bigl(x - (mw + 1) \bigl) +\dotso+ (y - mh)\times{\color[RGB]{255,0,0} (x - width)}
$$

$$
\normalsize + \bigl(y - (mh + 1) \bigl)\times(x - mw) + \bigl(y - (mh + 1) \bigl)\times\bigl(x - (mw + 1) \bigl) +\dotso+ \bigl(y - (mh + 1) \bigl)\times{\color[RGB]{255,0,0} (x - width)}
$$

$$
\vdots \qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad \vdots
$$

$$
\normalsize + {\color[RGB]{0,0,255}(y - height)}\times(x - mw) + {\color[RGB]{0,0,255}(y - height)}\times\bigl(x - (mw + 1) \bigl) +\dotso+ {\color[RGB]{0,0,255}(y - height)}\times{\color[RGB]{255,0,0} (x - width)}
$$

$$
{\color[RGB]{255,0,0} (x - width)} = x - \bigl(mw + width - mw)
$$

$$
{\color[RGB]{0,0,255}(y - height)} = y - \bigl(mh + height - mh)
$$

⇒ For the first line, we use the distributive property for (*y* - *mh*):

$$
\therefore (y - mh)\times(x - mw) + (y - mh)\times\bigl(x - (mw + 1) \bigl) +\dotso+ (y - mh)\times{\color[RGB]{255,0,0} (x - width)}
$$

$$
\normalsize = (y - mh) \times \Bigl(\bigl(x - mw) + \bigl(x - (mw + 1)) + \bigl(x - (mw + 2)) + \bigl(x - (mw + width - mw)))
$$

$$
\normalsize = (y - mh)\times\bigl(\underbrace{x\times(width - mw + 1)} - \underbrace{mw\times(width - mw + 1)} - \underbrace{\frac{(width - mw)\times(width - mw + 1)}{2}} \bigl)
$$

<ins>Formula1:</ins> Let a and b be integers, with b ≥ a. There are (b - a + 1) integers in the interval [a, b]. 

To find the number of occurrences of *x*, we consider the expressions (*x* - (*mw*)) and (*x* - (*mw* + *width* - *mw*)) from the first line. The pattern (*x* - (*mw*)), (*x* - (*mw* + 1)), (*x* - (*mw* + 2)), ...,(*x* - (*mw* + *width* - *mw*)) emerges from this. Subtracting *x* from this pattern gives us the remaining values, which we can use to determine how many times *x* occurs. In this case, we obtain the pattern *mw*, *mw* + 1, *mw* + 2, ..., *mw* + *width* - *mw*. We know that (*mw* + *width* - *mw*), so the value of *width*, is greater than or equal to *mw*. According to the Formula1, there are ((*mw* + *width* - *mw*) - (*mw*) + 1) *x*. So, there are (*width* - *mw* +1) *x*.

After calculating the value of *x*, we need to calculate the sum of all numbers subtracted from *x*.  

If we use the pattern *mw*, *mw* + 1, *mw* + 2, ..., *mw* + *width* - *mw*, we can see that there are *mw* in the range [*mw*, *width*] equal to the number of integers. In other words, according to the Formula1 there are (*width* - *mw* + 1) *mw*.

Finally, we need to sum the remaining numbers in our hands. 

<ins>Formula2:</ins> Let b be integers, with b ≥ 1. The sum of all integers in the interval [1, b] is (*b*.(*b*+1)/2).  

Let's consider the pattern (*x*-*mw*), (*x*-(*mw*+1)), (*x*-(*mw*+2)), ...,(*x*-(*mw* + *width* - *mw*)). We calculated how many *x* and *mw* numbers are. When we subtract *x* from the pattern, we are left with *mw*, *mw* + 1, *mw* + 2, ..., *mw* + *width* - *mw*. After subtracting *mw* as well, we have 0, 1, 2, ..., *width* - *mw* remaining in our hands. Therefore, we need to sum all integers in the range [0, *width* - *mw*]. According to the Formula2, the sum of these numbers is ((*width* - *mw*)(*width* - *mw* + 1) / 2).

⇒ We use the distributive property for the last expression:

$$
\normalsize \therefore (y - mh)\times\bigl(x\times(width - mw + 1) - mw\times(width - mw + 1) - \frac{(width - mw)\times(width - mw + 1)}{2} \bigl)
$$

$$
\normalsize = (y - mh)\times\Bigl((width - mw + 1)\times\bigl((x - mw - (\frac{width - mw} {2})\bigl)\Bigl)
$$

⇒ We said *x* = *width* + 1.

$$
\normalsize \therefore (y - mh)\times\Bigl(\frac {(width - mw +1)\times\bigl((width +1 - mw)\times 2 - width + mw\bigl)} {2}\Bigl)
$$

$$
\normalsize = (y - mh)\times\bigl(\frac{(width-mw+1)\times(2\times width + 2 -2\times mw - width + mw)}{2}\bigl)
$$

$$
\normalsize = (y - mh)\times\bigl(\frac{(width-mw+1)\times(width - mw + 2)}{2}\bigl)
$$

⇒ The last statement is the simplest form of the first line. Let's apply the simplification to the entire expression.

$$
\normalsize \therefore \displaystyle\sum\limits_{mh = minHeight}^{height} \displaystyle\sum\limits_{mw = minwidth}^{width} (height + 1 - mh)\times(width + 1 - mw)
$$

$$
\normalsize = (y - mh)\times\bigl(\frac{(width-mw+1)\times(width - mw + 2)}{2}\bigl)
$$

$$
\normalsize = \bigl(y - (mh + 1)\bigl)\times\bigl(\frac{(width-mw+1)\times(width - mw + 2)}{2}\bigl)
$$

$$
\vdots
$$

$$
\normalsize = \bigl(y - (mh + height - mh)\bigl)\times\bigl(\frac{(width-mw+1)\times(width - mw + 2)}{2}\bigl)
$$

⇒ For the first line, we use the distributive property again for ((*width* - *mw* + 1)x(*width* - *mw* + 2) / 2).

$$
\normalsize \therefore (y - mh)\times\bigl(\frac{(width-mw+1)\times(width - mw + 2)}{2}\bigl)
$$

$$
\normalsize = \bigl(\frac{(width - mw + 1)\times(width - mw + 2)}{2}\bigl)\times\underbrace{\Bigl(\bigl(y - mh) + \bigl(y - (mh + 1)\bigl) +\dotso+ \bigl(y - (mh + height -mh)\bigl)}\Bigl)
$$

⇒ Actually the same situation as we first calculated.

$$
\normalsize \bigl(x - mw\bigl) + \bigl(x - (mw + 1)\bigl) + \dotso + \bigl(x - (mw + width - mw)\bigl)
$$

was equal to

$$
\normalsize \frac{(width - mw + 1)\times(width - mw + 2)}{2}.
$$

So in the above operation is equal to

$$
\normalsize \frac{(height - mh + 1)\times(height - mh + 2)}{2}.
$$

$$
\normalsize \therefore \bigl(\frac{(width - mw + 1)\times(width - mw + 2)}{2}\bigl)\times\Bigl(\bigl(y - mh) + \bigl(y - (mh + 1)\bigl) +\dotso+ \bigl(y - (mh + height -mh)\bigl)\Bigl)
$$

$$
\normalsize = \bigl(\frac{(width - mw + 1)\times(width - mw + 2)}{2}\bigl)\times\bigl(\frac{(height - mh + 1)\times(height - mh + 2)}{2}\bigl)
$$

$$
\normalsize = \bigl(\frac{(width - mw + 1)\times(width - mw + 2)\times(height - mh + 1)\times(height - mh + 2)}{2}\bigl)
$$

⇒ Thanks to this formula, we can calculate the sections with a minimum pixel size of *minWidth*x*minHeight* size. However, the pixel sizes of this table can be changed place, which means that *minWidth* can be equal to *minHeight*, and *minHeight* can be equal to *minWidth*. That is, *width* changes place with *height*. If the minimum pixel size is *a*x*b* initially, in *width*x*height* format, it can also be *b*x*a*. Therefore, we need to find the number of unions of the clusters obtained from these two minimum pixel sizes.

$$
\normalsize P = [a \times b, ..., width \times height] \Rightarrow s(P) = \frac{(width- a + 1)(width - a + 2)(height - b + 1)(height - b + 2)}{4}
$$

$$
\normalsize Q = [b \times a, ..., width \times height] \Rightarrow s(Q) = \frac{(width- b + 1)(width - b + 2)(height - a + 1)(height - a + 2)}{4}
$$

$$
\normalsize s(P \cup Q) = s(P) + s(Q) - s(P \cap Q)
$$

If *a* < *b* <= *width*:

$$
\normalsize s(P \cup Q) = s(P) + s(Q) - s([b \times b, ..., width \times height])
$$

$$
\normalsize = \frac{(width- a + 1)(width - a + 2)(height - b + 1)(height - b + 2)}{4}
$$

$$
\normalsize + \frac{(width- b + 1)(width - b + 2)(height - a + 1)(height - a + 2)}{4}
$$

$$
\normalsize - \frac{(width - b + 1)(width - b + 2)(height - b + 1)(height - b + 2)}{4}
$$

If *b* < *a* <= *height* :

$$
\normalsize s(P \cup Q) = s(P) + s(Q) - s([a \times a, ..., width \times height])
$$

$$
\normalsize = \frac{(width- a + 1)(width - a + 2)(height - b + 1)(height - b + 2)}{4}
$$

$$
\normalsize + \frac{(width- b + 1)(width - b + 2)(height - a + 1)(height - a + 2)}{4}
$$

$$
\normalsize - \frac{(width - a + 1)(width - a + 2)(height - a + 1)(height - a + 2)}{4}
$$

If *a* = *b*:

$$
\normalsize s(P \cup Q) = \underbrace{s(P)} + \underbrace{s(Q)} - \underbrace{s(P \cap Q)}
$$

$$
\normalsize s(P \cup Q) = k + k - k = 
$$

$$
\normalsize s(P)
$$

$$
\normalsize \oplus
$$

$$
\normalsize s(Q)
$$

$$
\normalsize \oplus
$$

$$
\normalsize s([a \times a, ..., width \times height])
$$

$$
\normalsize \oplus
$$

$$
\normalsize s([b \times b, ..., width \times height])
$$

$$
\normalsize = \frac{(width- a + 1)(width - a + 2)(height - b + 1)(height - b + 2)}{4}
$$

$$
\normalsize \oplus
$$

$$
\normalsize = \frac{(width- b + 1)(width - b + 2)(height - a + 1)(height - a + 2)}{4}
$$

$$
\normalsize \oplus
$$

$$
\normalsize = \frac{(width- a + 1)(width - a + 2)(height - a + 1)(height - a + 2)}{4}
$$

$$
\normalsize \oplus
$$

$$
\normalsize = \frac{(width- b + 1)(width - b + 2)(height - b + 1)(height - b + 2)}{4}
$$

---
## Technologies
* (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0
* Visual Studio Vode version 1.80.0
* [Arbitrary-sized integer class for C++ (aka BigInt class) by Syed Faheel Ahmad](https://github.com/faheel/BigInt)

---
## Setup
* Download, compile, and run.
* It is a console/command-line application.
* It is recommended not to change the file hierarchy. If you are going to modify the file hierarchy, make sure to correctly adjust the paths of all included header files.

---
## Features
Finds all possible sections with minimum *a*x*b* pixel size in anything 2D and rectangular that can be represented by pixel dimensions. It also includes the minimum *b*x*a* pixel dimensions in the calculation. Returns the result as (cardinality of the set *a*x*b*) + (cardinality of the set *b*x*a*) - (cardinality of intersection of *a*x*b* set and *b*x*a* set). However, it also has methods to calculate sections specifically for *a*x*b* or *b*x*a* pixel sizes.

Although the algorithm may seem related to artworks, the phrase "art" there is just a reference to where the inspiration comes from. You can find more information in the [inspiration](#inspiration) section.

---
## Status
With the exception of bug fixes (if any), development of this project is complete.

---
## Inspiration
https://twitter.com/EjderAysunn/status/1674883836935561217

While examining the masterpiece below, I noticed that regardless of where I take a section at least 480x270 or 270x480 pixel size (this minimum reference size can be larger or smaller according to your preference), each section maintained its style and did not compromise its essence. In other words, every piece extracted from this masterpiece, meeting the minimum size requirement, was without exception a masterpiece in itself. This led me to wonder how many masterpieces were hidden within this masterpiece, prompting me to conduct this study.

### Adoration of Pan, by Johfra Bosschart, oil on panel, 1979  

![The_Adoration_of_Pan](https://github.com/EjderAysun/algorithm-for-counting-all-possible-sections-that-have-a-min-pixel-size-of-axb-and-bxa-in-artworks/assets/71559273/d13f30b0-aab8-454f-a4fb-6ec9ddce20d1)
![randomly_sectioned_adoration_of_pan](https://github.com/EjderAysun/algorithm-for-counting-all-possible-sections-that-have-a-min-pixel-size-of-axb-and-bxa-in-artworks/assets/71559273/55d2d62d-099a-44de-b0bb-f83827177983)
---
## Version
**Version 1.0.0**  

---
## Contributors
Ejder Aysun <ejderaysunn@gmail.com>  
BigInt Project by Syed Faheel Ahmad

The BigInt project is protected by the MIT license and is developed by Syed Faheel Ahmad. In this project, I have used certain parts of the BigInt project, modified some parts according to this project, removed certain parts, and left some parts usable, which could assist in modifying the algorithm in this project or contribute to the contributors of this project. The modified sections are indicated within the respective files. If you need more than what is available in this repository to contribute to this project or if you want to learn more about the BigInt project and contribute to it, you can review the project through this link: https://github.com/faheel/BigInt.

---
## Licence & Copyright
© Ejder Aysun, Algorithm for Counting All Possible Sections that Have a Min Pixel Size of axb and bxa in Artworks  
Licensed under the [MIT Licence](https://github.com/EjderAysun/algorithm-for-counting-all-possible-sections-that-have-a-min-pixel-size-of-axb-and-bxa-in-artworks/blob/main/LICENCE)