#include "MyRunAction.hh"
#include "MyDetectorConstruction.hh"
#include "MyPrimaryGeneratorAction.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include <fstream>
#include "G4UnitsTable.hh"

MyRunAction::MyRunAction(MyDetectorConstruction* myDetectorConstruction,
						MyPrimaryGeneratorAction* myGeneratorAction,
						const G4String& physicsListName)
:
G4UserRunAction(),
myDetectorConstruction(myDetectorConstruction),
myGeneratorAction(myGeneratorAction),
physicsListName(physicsListName)
{

}

MyRunAction::~MyRunAction() {}

void MyRunAction::BeginOfRunAction(const G4Run*)
{
}

void MyRunAction::EndOfRunAction(const G4Run*)
{
	G4String fileName = "./vis-dynamicLabels.macro";

	std::ofstream outFile;
	outFile.open(fileName);
	// Create and write to the file if it doesn't exit, otherwise overwrite it
	if (outFile.is_open())
	{
		outFile << "#ParticleGun:" << G4endl;
		outFile << "/vis/set/textColour cyan" << G4endl;
		outFile << "/vis/scene/add/text2D -0.9 0.7 12 ! ! gun particle: "
				<< myGeneratorAction->GetLabelParticleGunName()
				<< G4endl;

		G4String particleGunEnergyAndUnit
		= G4BestUnit(myGeneratorAction->GetLabelParticleGunEnergy(), "Energy");
		outFile << "/vis/scene/add/text2D -0.9 0.6 12 ! ! gun energy: "
				+ particleGunEnergyAndUnit
				<< G4endl;

		outFile << "/vis/scene/add/text2D -0.9 0.5 12 ! ! physics list: "
				<< physicsListName
				<< G4endl;

//		outFile << "#Particle colour codes:" << G4endl;
//		outFile << "/vis/scene/add/text2D -0.9 0.4 12 ! ! particle colour codes:" << G4endl;

		G4String particle{"neutron"};
		G4String colour{"yellow"};
		outFile << "/vis/modeling/trajectories/drawByParticleID-0/set "
				<< particle << " " << colour << G4endl;
		outFile << "/vis/set/textColour " + colour  << G4endl;
		outFile << "/vis/scene/add/text2D -0.9 0.3 12 ! ! "
				<< particle << G4endl;

		particle = "anti_neutron";
		colour = "magenta";
		outFile << "/vis/modeling/trajectories/drawByParticleID-0/set "
				<< particle << " " << colour << G4endl;
		outFile << "/vis/set/textColour " + colour  << G4endl;
		outFile << "/vis/scene/add/text2D -0.75 0.3 12 ! ! "
				<< particle << G4endl;

		particle = "proton";
		colour = "white";
		outFile << "/vis/modeling/trajectories/drawByParticleID-0/set "
				<< particle << " " << colour << G4endl;
		outFile << "/vis/set/textColour " + colour  << G4endl;
		outFile << "/vis/scene/add/text2D -0.9 0.2 12 ! ! "
				<< particle << G4endl;

		particle = "anti_proton";
		colour = "cyan";
		outFile << "/vis/modeling/trajectories/drawByParticleID-0/set "
				<< particle << " " << colour << G4endl;
		outFile << "/vis/set/textColour " + colour  << G4endl;
		outFile << "/vis/scene/add/text2D -0.75 0.2 12 ! ! "
				<< particle << G4endl;

		particle = "alpha";
		colour = "blue";
		outFile << "/vis/modeling/trajectories/drawByParticleID-0/set "
				<< particle << " " << colour << G4endl;
		outFile << "/vis/set/textColour " + colour  << G4endl;
		outFile << "/vis/scene/add/text2D -0.9 0.1 12 ! ! "
				<< particle << G4endl;

		particle = "anti_alpha";
		colour = "red";
		outFile << "/vis/modeling/trajectories/drawByParticleID-0/set "
				<< particle << " " << colour << G4endl;
		outFile << "/vis/set/textColour " + colour  << G4endl;
		outFile << "/vis/scene/add/text2D -0.75 0.1 12 ! ! "
				<< particle << G4endl;

		particle = "gamma";
		colour = "green";
		outFile << "/vis/modeling/trajectories/drawByParticleID-0/set "
				<< particle << " " << colour << G4endl;
		outFile << "/vis/set/textColour " + colour  << G4endl;
		outFile << "/vis/scene/add/text2D -0.9 0.0 12 ! ! "
				<< particle << G4endl;

		particle = "other particles";
		colour = "grey";
		outFile << "/vis/set/textColour " + colour  << G4endl;
		outFile << "/vis/scene/add/text2D -0.75 0.0 12 ! ! "
				<< particle << G4endl;

//		particle = "positron";
//		colour = "blue";
//		outFile << "/vis/modeling/trajectories/drawByParticleID-0/set "
//				<< particle << " " << colour << G4endl;
//		outFile << "/vis/set/textColour " + colour  << G4endl;
//		outFile << "/vis/scene/add/text2D -0.9 -0.1 12 ! ! "
//				<< particle << G4endl;
//
//		particle = "GenericIon";
//		colour = "grey";
//		outFile << "/vis/modeling/trajectories/drawByParticleID-0/set "
//				<< particle << " " << colour << G4endl;
//		outFile << "/vis/set/textColour " + colour  << G4endl;
//		outFile << "/vis/scene/add/text2D -0.75 -0.1 12 ! ! "
//				<< particle << G4endl;

		colour = "yellow";
		outFile << "/vis/set/textColour " + colour  << G4endl;
		outFile << "/vis/scene/add/text2D -0.9 -0.2 12 ! ! yellow dots: Monte Carlo steps"
				<< G4endl;

//		if (myDetectorConstruction->GetDisplayMaterialLabels())
//		{
//		Labels syntax:
//		/vis/scene/add/text x y z unit font_size x_offset y_offset text
//		Adds text at (x*unit, y*unit, z*unit) with font_size x_offset y_offset
//		Font size and offsets in pixels

			outFile << "#LabMaterial:" << G4endl;
			outFile << "/vis/set/textColour white" << G4endl;
			outFile << "/vis/scene/add/text -25 -25 -25 cm 10 0 0 lab: "
					+ myDetectorConstruction->GetLabMaterial() << G4endl;

			outFile << "#TargetMaterial:" << G4endl;
			outFile << "/vis/scene/add/text -10 -5 15 cm 10 0 0 target: "
					+ myDetectorConstruction->GetTargetMaterial() << G4endl;

			if (myDetectorConstruction->GetShieldOn())
			{
				outFile << "#ShieldMaterial:" << G4endl;
				outFile << "/vis/scene/add/text -10 -5 -11 cm 10 0 0 radiation shield: "
						<<	myDetectorConstruction->GetShieldMaterial() << G4endl;

			}
//		}

		outFile << "#Scale interval set to yellow colour:" << G4endl;
		outFile << "/vis/set/textColour yellow" << G4endl;
		outFile << "/vis/scene/add/scale" << G4endl;

		outFile.close();
//		G4cout << "Text written to file " << fileName << G4endl;

		G4UImanager *uiManager = G4UImanager::GetUIpointer();
		uiManager->ApplyCommand("/control/execute vis-reInit.macro");
		uiManager->ApplyCommand("/control/execute vis-dynamicLabels.macro");
	}
	else
	{
		G4cerr << "Could not create file " << fileName << G4endl;
	}
}
