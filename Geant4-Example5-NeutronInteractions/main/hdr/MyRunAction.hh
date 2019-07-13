#ifndef HDR_MYRUNACTION_HH_
#define HDR_MYRUNACTION_HH_

#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;
class MyDetectorConstruction;
class MyPrimaryGeneratorAction;

class MyRunAction: public G4UserRunAction
{
public:
	MyRunAction(MyDetectorConstruction *myDetectorConstruction,
				MyPrimaryGeneratorAction *myGeneratorAction,
				const G4String& physicsListName);
	virtual ~MyRunAction();

	virtual void BeginOfRunAction(const G4Run* run);
	virtual void EndOfRunAction(const G4Run* run);

	void SetPhysicsListName(const G4String& physicsListName) {
		this->physicsListName = physicsListName;
	}

private:
	MyDetectorConstruction *myDetectorConstruction;
	MyPrimaryGeneratorAction *myGeneratorAction;
	G4String physicsListName;
};

#endif /* HDR_MYRUNACTION_HH_ */
