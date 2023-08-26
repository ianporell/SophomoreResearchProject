# SophomoreResearchProject
Effect of password complexity on time taken to crack hashed password by brute force

Prediction: Exponential Growth with increased password complexity is modeled by the following equation:
![equation](https://latex.codecogs.com/svg.image?&space;f(x,y,z)=\sum_{i=1}^{z-1}(y^i)&plus;\sum_{i=z}^{1}((x_{i}-1)*y^{z-i})&plus;1)<br>
Where x is a set representing the string by mapping each character to its index in the charset, y is the length of the charset, and z is the length of the set.

