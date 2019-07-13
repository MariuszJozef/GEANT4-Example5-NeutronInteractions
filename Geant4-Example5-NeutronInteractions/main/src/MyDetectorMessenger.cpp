#include "MyDetectorMessenger.hh"
#include "MyDetectorConstruction.hh"

#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcommand.hh"

MyDetectorMessenger::MyDetectorMessenger(MyDetectorConstruction* myDetectorConstruction)
: G4UImessenger(),
  myDetectorConstruction(myDetectorConstruction)
{
	labMaterialUiCmd = new G4UIcmdWithAString("/material/lab", this);
	labMaterialUiCmd->SetGuidance("Select Material of the laboratory.");
	labMaterialUiCmd->SetParameterName("newLabMaterial",false);
	labMaterialUiCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

	targetMaterialUiCmd = new G4UIcmdWithAString("/material/target", this);
	targetMaterialUiCmd->SetGuidance("Select Material of the target.");
	targetMaterialUiCmd->SetParameterName("newTargetMaterial",false);
	targetMaterialUiCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

	shieldMaterialUiCmd = new G4UIcmdWithAString("/material/shield", this);
	shieldMaterialUiCmd->SetGuidance("Select Material of the shield.");
	shieldMaterialUiCmd->SetParameterName("newShieldMaterial",false);
	shieldMaterialUiCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

	shieldSwitchOnOffUiCmd = new G4UIcmdWithABool("/radiationShield/switchOn", this);
	shieldSwitchOnOffUiCmd->SetGuidance("Switch radiation shield on or off");
	shieldSwitchOnOffUiCmd->SetParameterName("radiationShieldOn", false);
	shieldSwitchOnOffUiCmd->SetDefaultValue(true);
	shieldSwitchOnOffUiCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

	shieldThicknessUiCmd = new G4UIcmdWithADoubleAndUnit("/radiationShield/thickness", this);
	shieldThicknessUiCmd->SetGuidance("Set thickness of the radiation shield");
	shieldThicknessUiCmd->SetParameterName("radiationShieldThickness", false);
	shieldThicknessUiCmd->SetDefaultUnit("cm");
	shieldThicknessUiCmd->SetDefaultValue(5.5*cm);
	shieldThicknessUiCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

	// START OF MY CUSTOM COMMAND
	activeRotationAxisAngleCustomUiCmd = new G4UIcommand("/target/rotationAxisAngle",
			this);
	activeRotationAxisAngleCustomUiCmd->SetGuidance(
			"Set rotation axis and angle: x, y, z, angle, angularUnit");

	G4UIparameter *setRotationXaxisPrm = new G4UIparameter("rotationAxisComponentX", 'd',
			false);
	setRotationXaxisPrm->SetGuidance("X component of rotation axis");
	//	Is this next line redundant?
	setRotationXaxisPrm->SetParameterName("rotationAxisComponentX");
	activeRotationAxisAngleCustomUiCmd->SetParameter(setRotationXaxisPrm);

	G4UIparameter *setRotationYaxisPrm = new G4UIparameter("rotationAxisComponentY", 'd',
			false);
	setRotationYaxisPrm->SetGuidance("Y component of rotation axis");
	setRotationYaxisPrm->SetParameterName("rotationAxisComponentY");
	activeRotationAxisAngleCustomUiCmd->SetParameter(setRotationYaxisPrm);

	G4UIparameter *setRotationZaxisPrm = new G4UIparameter("rotationAxisComponentZ", 'd',
			false);
	setRotationZaxisPrm->SetGuidance("Z component of rotation axis");
	setRotationZaxisPrm->SetParameterName("rotationAxisComponentZ");
	activeRotationAxisAngleCustomUiCmd->SetParameter(setRotationZaxisPrm);

	G4UIparameter *setRotationAnglePrm = new G4UIparameter("rotationAngle", 'd', false);
	setRotationAnglePrm->SetGuidance("Angle of rotation about the rotation axis");
	setRotationAnglePrm->SetParameterName("rotationAngle");
	activeRotationAxisAngleCustomUiCmd->SetParameter(setRotationAnglePrm);

	G4UIparameter *setUnitOfRotationAnglePrm = new G4UIparameter("rotationAngleUnit", 's',
			false);
	setUnitOfRotationAnglePrm->SetGuidance("Unit of rotation angle: deg or rad");
	// setUnitOfRotationAnglePrm->SetParameterName("rotationAngleUnit");
	G4String angleUnitList = G4UIcommand::UnitsList(G4UIcommand::CategoryOf("deg"));
	angleUnitList += " ";
	angleUnitList += G4UIcommand::UnitsList(G4UIcommand::CategoryOf("rad"));
	setUnitOfRotationAnglePrm->SetParameterCandidates(angleUnitList);
	//	setUnitOfRotationAnglePrm->SetDefaultUnit("deg"); // doesn't exist
	activeRotationAxisAngleCustomUiCmd->SetParameter(setUnitOfRotationAnglePrm);

	activeRotationAxisAngleCustomUiCmd->AvailableForStates(G4State_PreInit,
			G4State_Idle);
	activeRotationAxisAngleCustomUiCmd->SetToBeBroadcasted(false);
	// END OF MY CUSTOM COMMAND
}

MyDetectorMessenger::~MyDetectorMessenger()
{
	delete labMaterialUiCmd;
	delete targetMaterialUiCmd;
	delete shieldMaterialUiCmd;
	delete shieldSwitchOnOffUiCmd;
	delete shieldThicknessUiCmd;
	delete activeRotationAxisAngleCustomUiCmd;
}

void MyDetectorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
	if (command == labMaterialUiCmd)
	{
		if (newValue == "vacuum")
			newValue = "G4_Galactic";
		myDetectorConstruction->SetLabMaterial(newValue);
	}
	else if (command == targetMaterialUiCmd)
	{
		myDetectorConstruction->SetTargetMaterial(newValue);
	}
	else if (command == shieldMaterialUiCmd)
	{
		myDetectorConstruction->SetShieldMaterial(newValue);
	}
	else if (command == shieldThicknessUiCmd)
	{
		myDetectorConstruction->SetShieldThickness(
				shieldThicknessUiCmd->GetNewDoubleValue(newValue));
	}
	else if (command == shieldSwitchOnOffUiCmd)
	{
		myDetectorConstruction->SetShieldOn(
				shieldSwitchOnOffUiCmd->GetNewBoolValue(newValue));
	}
	else if (command == activeRotationAxisAngleCustomUiCmd)
	{
		G4double rotationAxisX, rotationAxisY, rotationAxisZ, rotationAngle;
		G4String rotationAngleUnit;

		std::istringstream is(newValue);
		is >> rotationAxisX >> rotationAxisY >> rotationAxisZ >> rotationAngle >> rotationAngleUnit;

		G4ThreeVector rotationAxis = G4ThreeVector(rotationAxisX, rotationAxisY, rotationAxisZ);
		rotationAngle *= G4UIcommand::ValueOf(rotationAngleUnit);

		myDetectorConstruction->SetActiveRotationAxisAngle(rotationAxis, rotationAngle);
	}

}

G4String MyDetectorMessenger::GetCurrentValue(G4UIcommand* command)
{
	G4String currentValue;

	if (command == labMaterialUiCmd)
	{
		currentValue = myDetectorConstruction->GetLabMaterial();
		if (currentValue == "G4_Galactic")
			currentValue = "vacuum (G4_Galactic)";
	}
	else if (command == targetMaterialUiCmd)
	{
		currentValue = myDetectorConstruction->GetTargetMaterial();
	}
	else if (command == shieldMaterialUiCmd)
	{
		currentValue = myDetectorConstruction->GetShieldMaterial();
	}
	else if (command == shieldThicknessUiCmd)
	{
		currentValue = shieldThicknessUiCmd->ConvertToString(
				myDetectorConstruction->GetShieldThickness(), "cm");
	}
	else if (command == shieldSwitchOnOffUiCmd)
	{
		currentValue = shieldSwitchOnOffUiCmd->ConvertToString(
				myDetectorConstruction->GetShieldOn());
	}
	else if (command == activeRotationAxisAngleCustomUiCmd)
	{
//		Display rotationAxis with opposite sign to what is used internally for calculating (passive)
//		G4RotationMatrix because user inputs active (not passive) rotations; output should coincide
//		with input.
		G4ThreeVector rotationAxis = -myDetectorConstruction->GetRotationAxis();
		G4double rotationAngle = myDetectorConstruction->GetRotationAngle();
		currentValue = activeRotationAxisAngleCustomUiCmd->ConvertToString(rotationAxis);
		currentValue += " ";
		currentValue += activeRotationAxisAngleCustomUiCmd->ConvertToString(rotationAngle, "deg");
	}

	return currentValue;
}
