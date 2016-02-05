Object Recognition System base on Opencv and Qt.
We followed three step to build this system.
1.Feature representation : use SIFT and SURF algorithm to detect and describe local features in images.
2.Codebook generation: performek-means clustering over all the vectors to convert vector-represented patches to "codewords" 
3.Learning and recognition based on the BoW model:apply support vector machine (SVM) algoriothm to train and recongnition objects. Kernel trick is also appllied.

