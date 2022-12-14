# UOC
We provide underwater optical communication (uoc) module that is implemented using ns-3.24.1 to simulate small-scale UOC networks.Please refer to the doc directory for more details.

If you do not have ns-3 installed in your PC, please refer to the following link for installation:  

https://www.nsnam.org/docs/release/3.24/tutorial/singlehtml/index.html 
Installation guide: https://www.nsnam.org/wiki/Installation (Follow the instructions for installation depending on which flavor of Linux you prefer)

Once an example script is made and compiles, to run this script it must be in the scratch directory:
To get to this directory run the cmd: cd repos/ns-3-allinone/ns-3-dev/scratch (path is not fixed also it depends on which ns-3 version you install)

ns-3 file documentation: https://www.nsnam.org/doxygen/index.html (gives an idea of ns-3 classes structure)

Steps to install UOC module in ns-3: 

Prerequisites:

1-Having the ns-3 environment installed and running in your linux environment


Installation:

1) download .zip file of the UOC module

2) open .zip file and you should see a simple folder named uocnew

3) enter that folder and you should see folders that mimic the ones in the repository

4) Now, go into the terminal and build a skeleton module by typing "./create-module.py uocnew" (please follow ns-3 guidline on how to build new module)

5) Find your ns-3 file system and in the "src" folder there should be a "uocnew" folder, open that and you should see similar folder names to that of the repository.

6) you should delete those files as they will be replaced by the files downloaded from the repository

7) Look back to where you unziped the downloaded repository files and copy and paste those folders and files into this newly made folder (do not copy the scratch folder)

8) Now, start up the terminal and go to the ns-3-dev directory

9) While in this directory build all the ns-3 modules (if unsure use the installation guide to help, I use ubuntu and my command is ./waf vv)

10) It is optional to enable tests and examples but it should build regardless ( build will take sometimes! have your coffee ready!)

11)  now you can use the uocnew-module in ns-3 simulations


//Running a script

1) create a file a .cc file and follow the format that the example scripts use (in terms of laying out the script)

2) move the file into the /scratch directory (must run any test from the scratch directory)

3) to compile and run use the command "./waf --run scratch/your_file_name_without_.cc
