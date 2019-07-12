# GEANT4-Example5-NeutronInteractions
In this example the type of radiation-matter interactions can be selected via an input argument, argv, that is passed into the main function, i.e. main(int argc, char** argv). As the physics of neutron interactions is particularly difficult to model, for demonstration purposes several built-in GEANT4 physics lists are made available, namely: FTFP_BERT, FTFP_BERT_HP, QBBC, QGSP_BIC_HP; a suitable value of argv decides which one gets included into program compilation. The value passed into argv must be an exact, case sensitive match of the desired physics list name above.

Besides these lists above, a very important example of an explicit physics list with neutron interactions is furnished by GEANT4 example found in the extended/hadronic/Hadr06 directory of GEANT4 installation. The neutron physics code found therein is utilised here; it is placed (without significant changes) in the directory main/neutronPhysicsList-ExtendedHadr06. To choose this latter neutron physics list for compilation, the value passed into argv must be: neutronPhysicsList.

![](GEANT4-Example5-1.gif)

<img width="832" alt="image" src="https://user-images.githubusercontent.com/51378175/61155548-7fd12f80-a4f1-11e9-8276-4c88b08e5994.png">
