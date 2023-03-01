# Initial Ideas: 1 March 2023 #

The goal of this project is to "learn" application-specific features to assign common vision 3D reconstruction tasks:

* Stereo Matching
* Image Alignment

I want to initially demonstrate that this is possible using a random search type strategy. Once I have shown this, then the next step is to explore the notion of various feature representations. The initial first representation that I want to determine is almost the exact version of the type of representation that I would use in a CNN. This will work as follows:

* An initial "large" patch size of n x n.
* Each layer can have 32 5x5 filters + plus ReLU activation per pixel.
* A pooling layer that reduces the size of the patch by half
* Producing a feature vector that is compared using an inner project.

Some key points about the process:
* Features are precalculated from "gradient images" at the start of the process.
* They are used for correspondence matching - in conjunction with a known algorithm (let's try semi-global initially).
