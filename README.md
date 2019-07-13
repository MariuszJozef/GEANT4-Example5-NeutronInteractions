# GEANT4-Example5-NeutronInteractions
In this example the type of radiation-matter interactions can be selected via an input argument, argv, that is passed into the main function, i.e. main(int argc, char** argv). As the physics of neutron interactions is particularly difficult to model, here for demonstration purposes several built-in GEANT4 physics lists are made available, namely: FTFP_BERT, FTFP_BERT_HP, QBBC, QGSP_BIC_HP; a suitable value of argv decides which one gets included into program compilation. The value passed into argv must be an exact, case sensitive match of the desired physics list name above. (Cf. screenshots at the end of the README).

Besides these lists above, a very important example of an explicit physics list with neutron interactions is furnished by GEANT4 example found in the extended/hadronic/Hadr06 directory of GEANT4 installation. The neutron physics code found therein is utilised here; it is placed (without significant changes) into the directory main/neutronPhysicsList-ExtendedHadr06. To choose this latter neutron physics list for compilation, the value passed into argv must be: neutronPhysicsList.

# A neutron randomly rebounds off of water nuclei:

![](GEANT4-Example5-1.gif)

# A single incident neutron ejects multiple other neutrons and nuclear fragments from fissile uranium!  

![](GEANT4-Example5-2.gif)

![](GEANT4-Example5-3.gif)

![](GEANT4-Example5-4.gif)

![](GEANT4-Example5-5b.gif)

![](GEANT4-Example5-6.gif)

![](GEANT4-Example5-7.gif)

# Input argument to select a physics list
<img width="1149" alt="image" src="https://user-images.githubusercontent.com/51378175/61164753-6db6b780-a518-11e9-84da-4139ea617b7e.png">

<img width="1070" alt="image" src="https://user-images.githubusercontent.com/51378175/61164951-a48dcd00-a51a-11e9-9398-8ae19903b9df.png">

<img width="794" alt="image" src="https://user-images.githubusercontent.com/51378175/61164910-31845680-a51a-11e9-8748-d69d96992426.png">
