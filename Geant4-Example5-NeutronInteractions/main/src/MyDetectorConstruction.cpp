#include "MyDetectorConstruction.hh"
#include "MyDetectorMessenger.hh"

#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4Box.hh"
#include "G4Trd.hh"
#include "G4Tubs.hh"

#include "G4NistManager.hh"
#include "G4VisAttributes.hh"
#include "G4RunManager.hh"
#include "G4RotationMatrix.hh"

MyDetectorConstruction::MyDetectorConstruction()
:
G4VUserDetectorConstruction(),
halfLabSize(G4ThreeVector(30*cm, 30*cm, 30*cm))
{
	myDetectorMessenger = new MyDetectorMessenger(this);
	SetActiveRotationAxisAngle(G4ThreeVector(0, 1, 0), 5*deg);
}

MyDetectorConstruction::~MyDetectorConstruction()
{

	delete myDetectorMessenger;
}

G4VPhysicalVolume* MyDetectorConstruction::Construct()
{
	DefineMaterials();
	return ConstructDetector();
}

void MyDetectorConstruction::DefineMaterials()
{
	G4NistManager *nist = G4NistManager::Instance();
	G4Material *vacuum = nist->FindOrBuildMaterial("G4_Galactic");
	G4Material *air = nist->FindOrBuildMaterial("G4_AIR");
	G4Material *G4H2Oliquid = nist->FindOrBuildMaterial("G4_WATER");
	G4Material *G4H2Osteam = nist->FindOrBuildMaterial("G4_WATER_VAPOR");
	G4Material *G4Pb = nist->FindOrBuildMaterial("G4_Pb");
	G4Material *G4Concrete = nist->FindOrBuildMaterial("G4_CONCRETE");

	G4Material *skin = nist->FindOrBuildMaterial("G4_SKIN_ICRP");
	G4Material *softTissue = nist->FindOrBuildMaterial("G4_TISSUE_SOFT_ICRP");
	G4Material *muscle = nist->FindOrBuildMaterial("G4_MUSCLE_WITH_SUCROSE");
	G4Material *bone = nist->FindOrBuildMaterial("G4_BONE_COMPACT_ICRU");

	G4String name, symbol;
	G4double abundance, density, temperature, pressure;
	G4double a; 					// mass of a mole
	G4double z; 					// atomic number (number of protons);
	G4int components, nucleons, numberOfIsotopes, numberOfAtoms, fractionmass;

	G4Material *Al = new G4Material("Aluminium", z=13, a=26.98*g/mole, density=2.7*g/cm3);
	G4Material *Pb = new G4Material("Lead", z=82, a= 207.19*g/mole, density= 11.35*g/cm3);
	G4Material *Ti = new G4Material("Titanium", z=22, a=47.867*g/mole, density=4.54*g/cm3);

	G4Element *Cs = new G4Element("Cesium", symbol="Cs", z=55, a=132.9*g/mole);
	G4Element *I = new G4Element("Iodine", symbol="I", z=53, a=126.9*g/mole);
	G4Material *CsI = new G4Material("CsI", density=4.51*g/cm3, components=2);
	CsI->AddElement(I, .5);
	CsI->AddElement(Cs, .5);

	// graphite
	G4Isotope* C12isotope = new G4Isotope("C12", z=6, nucleons=12);
	G4Element* C12element = new G4Element("Graphite","C12", components=1);
	C12element->AddIsotope(C12isotope, 100.*perCent);
	G4Material* graphite = new G4Material("graphite",
										density=2.27*g/cm3,
										components=1,
										kStateSolid,
										temperature=293*kelvin,
										pressure=1*atmosphere);
	graphite->AddElement(C12element, numberOfAtoms=1);

	// pressurized water
	G4Element *H  = new G4Element("Hydrogen","H", z=1, a=1.0079*g/mole);
	G4Element *O  = new G4Element("Oxygen","O", z=8, a=16.00*g/mole);
	G4Material *H2Opressurised = new G4Material("pressurised water",
									density=1.000*g/cm3,
									components=2,
									kStateLiquid,
									temperature=593*kelvin,
									pressure=150*bar);
	H2Opressurised->AddElement(H, numberOfAtoms=2);
	H2Opressurised->AddElement(O, numberOfAtoms=1);
	H2Opressurised->GetIonisation()->SetMeanExcitationEnergy(78.0*eV);

	// heavy water
	G4Isotope* Deuteron = new G4Isotope("Deuteron", z=1, nucleons=2);
	G4Element* Deuterium  = new G4Element("Deuterium", "Deuterium", numberOfIsotopes=1);
	Deuterium->AddIsotope(Deuteron, 100*perCent);
	G4Material* D2O = new G4Material("heavy water",
									density=1.11*g/cm3,
									components=2,
									kStateLiquid,
									temperature=293.15*kelvin,
									pressure=1*atmosphere);
	D2O->AddElement(Deuterium, numberOfAtoms=2);
	D2O->AddElement(O, numberOfAtoms=1);

	G4Isotope *U5 = new G4Isotope(name="U235", z=92, nucleons=235, a=235.01*g/mole);
	G4Isotope *U8 = new G4Isotope(name="U238", z=92, nucleons=238, a=238.03*g/mole);

	G4Element *UraniumElementEnriched10perCent =
			new G4Element(name="10% enriched Uranium", symbol="U", components=2);
	UraniumElementEnriched10perCent->AddIsotope(U5, abundance=90.*perCent);
	UraniumElementEnriched10perCent->AddIsotope(U8, abundance=10.*perCent);

	G4Element *UraniumElementEnriched20perCent =
			new G4Element(name="20% enriched Uranium", symbol="U", components=2);
	UraniumElementEnriched20perCent->AddIsotope(U5, abundance=80*perCent);
	UraniumElementEnriched20perCent->AddIsotope(U8, abundance=20*perCent);

	G4Material *UraniumMaterialEnriched10perCent =
			new G4Material(name="10% enriched Uranium",
							density=18.95*g/cm3, // verify this density!!
							components=1);
	UraniumMaterialEnriched10perCent->AddElement(UraniumElementEnriched10perCent, fractionmass=1);

	G4Material *UraniumMaterialEnriched20perCent =
			new G4Material(name="20% enriched Uranium",
							density=19.050*g/cm3, // from http://geant4.in2p3.fr/2007/prog/GiovanniSantin/GSantin_Geant4_Paris07_Materials_v08.pdf
							components=1,
							kStateSolid);
	UraniumMaterialEnriched20perCent->AddElement(UraniumElementEnriched20perCent, fractionmass=1);

	G4Element *F = new G4Element("Fluorine", "F", z=9., a=18.998*g/mole);

	G4Material *UraniumHexaFluoride = new G4Material("Uranium hexafluoride",
											density=5.09*g/cm3,
											components=2,
											kStateGas,
											temperature=640*kelvin,
											pressure=1.5e7*pascal);
	UraniumHexaFluoride->AddElement(F, 6);
	UraniumHexaFluoride->AddElement(UraniumElementEnriched10perCent, 1); // UF_6

//	Prevent changing materials to default values if they were adjusted at run time:
	if (labMaterial == nullptr)
		labMaterial = H2Opressurised;

	if (targetMaterial == nullptr)
		targetMaterial = UraniumMaterialEnriched10perCent;

	if (shieldMaterial == nullptr)

		shieldMaterial = D2O; // i.e. Heavy Water
//		shieldMaterial = G4Concrete;
}

G4VPhysicalVolume* MyDetectorConstruction::ConstructDetector()
{
	G4bool checkOverlaps = true;
	G4double opacity = 0.4;

	G4VisAttributes* invisible = new G4VisAttributes(G4Colour(1, 1, 1));
	invisible->SetVisibility(false);

	G4VisAttributes *orange = new G4VisAttributes(G4Colour(1, 0.65, 0, opacity));
	orange->SetVisibility(true);
	orange->SetForceWireframe(true); // Whichever is last overwrites the previous one!
	orange->SetForceSolid(true);     // Whichever is last overwrites the previous one!

	G4VisAttributes *yellow = new G4VisAttributes(G4Colour(1, 1, 0, opacity));
	yellow->SetVisibility(true);
	yellow->SetForceSolid(true);

	G4VisAttributes *brown = new G4VisAttributes(G4Colour(0.71, 0.4, 0.11, opacity));
	brown->SetVisibility(true);
	brown->SetForceSolid(true);

	G4VisAttributes *green = new G4VisAttributes(G4Colour(0, 1, 0, opacity));
	green->SetVisibility(true);
	green->SetForceSolid(true);


	solidLab = new G4Box("Lab",          // name
						halfLabSize.x(), halfLabSize.y(), halfLabSize.z());

	logicalLab = new G4LogicalVolume(solidLab,
									labMaterial,
									"Lab");      //name

	physicalLab = new G4PVPlacement(nullptr,   		 //no rotation
									G4ThreeVector(), //at (0,0,0)
									logicalLab,      //its logical volume
									"Lab",           //its name
									nullptr,       	 //its mother volume
									false,           //no boolean operation
									0);              //copy number

//	logicalLab->SetVisAttributes(invisible);

	G4double halfLengthX1 = 13*cm, halfLengthX2 = 7*cm;
	G4double halfLengthY1 = 8*cm, halfLengthY2 = 14*cm;
	G4double halfLengthZ = 5*cm;
	solidTarget = new G4Trd("Target",
								halfLengthX1, halfLengthX2,
								halfLengthY1, halfLengthY2,
								halfLengthZ);

	logicalTarget = new G4LogicalVolume(solidTarget,
									   targetMaterial,
									   "Target");

	G4RotationMatrix *rotationAxisAngle = new G4RotationMatrix(rotationAxis, rotationAngle);
	new G4PVPlacement(rotationAxisAngle,		// rotation
	                  G4ThreeVector(0, 0, 15*cm), 	// at (x,y,z)
					  logicalTarget,			// logical volume
	                  "Target",     			// name
	                  logicalLab, 		     	// logical mother volume
	                  false,           			// no boolean operations
	                  0,               			// copy number
	                  checkOverlaps); 			// checking overlaps

	logicalTarget->SetVisAttributes(yellow);

	if (shieldOn)
	{
		G4double innerRadius = 0, outerRadius = 12*cm;
		G4double angleMin = 0, angleMax = 360*deg;
		solidShield = new G4Tubs("Shield",
								innerRadius, outerRadius,
								shieldThickness,
								angleMin, angleMax);

		logicalShield = new G4LogicalVolume(solidShield,
											 shieldMaterial,
											 "Shield",
											 0, 0, 0);

		new G4PVPlacement(nullptr,				        // no rotation
						  G4ThreeVector(0, 0, -11*cm), 	// at (x,y,z)
						  logicalShield,				// its logical volume
						  "Shield",	      			// its name
						  logicalLab, 		    		// logical mother volume
						  false,           				// no boolean operations
						  0,               				// copy number
						  checkOverlaps); 				// checking overlaps

		logicalShield->SetVisAttributes(brown);
	}

	return physicalLab;
}

void MyDetectorConstruction::SetLabMaterial(const G4String& labMaterial)
{
	G4Material *ptrToMaterial = G4NistManager::Instance()->FindOrBuildMaterial(labMaterial);
	if (ptrToMaterial)
	{
		this->labMaterial = ptrToMaterial;
		if (logicalLab)
		{
			logicalLab->SetMaterial(this->labMaterial);
			G4RunManager::GetRunManager()->PhysicsHasBeenModified();
			G4cout << "Lab material changed to: " << GetLabMaterial() << G4endl;
		}
	}
	else
	{
		G4cerr << "Material not found" << G4endl;
	}
}

void MyDetectorConstruction::SetTargetMaterial(const G4String& targetMaterial)
{
	G4Material *ptrToMaterial = G4NistManager::Instance()->FindOrBuildMaterial(targetMaterial);
	if (ptrToMaterial)
	{
		this->targetMaterial = ptrToMaterial;
		if (logicalTarget)
		{
			logicalTarget->SetMaterial(this->targetMaterial);
			G4RunManager::GetRunManager()->PhysicsHasBeenModified();
			G4cout << "Target material changed to: " << GetTargetMaterial() << G4endl;
		}
	}
	else
	{
		G4cerr << "Material not found" << G4endl;
	}
}

void MyDetectorConstruction::SetShieldMaterial(const G4String& shieldMaterial)
{
	G4Material *ptrToMaterial = G4NistManager::Instance()->FindOrBuildMaterial(shieldMaterial);
	if (ptrToMaterial)
	{
		this->shieldMaterial = ptrToMaterial;
		if (logicalShield)
		{
			logicalShield->SetMaterial(this->shieldMaterial);
			G4RunManager::GetRunManager()->PhysicsHasBeenModified();
			G4cout << "Shield material changed to: " << GetShieldMaterial() << G4endl;
		}
	}
	else
	{
		G4cerr << "Material not found" << G4endl;
	}
}

void MyDetectorConstruction::SetShieldOn(G4bool shieldOn)
{
	this->shieldOn = shieldOn;
	G4RunManager::GetRunManager()->ReinitializeGeometry();
}

void MyDetectorConstruction::SetShieldThickness(G4double shieldThickness)
{
	this->shieldThickness = shieldThickness;
	G4RunManager::GetRunManager()->ReinitializeGeometry();
}

void MyDetectorConstruction::SetActiveRotationAxisAngle(G4ThreeVector rotationAxis, G4double rotationAngle)
{
	// Force this to be an active rather than a passive rotation
	this->rotationAxis = -rotationAxis;
	this->rotationAngle = rotationAngle;
//  Rotation effective immediately; removes beam:
//	G4RunManager::GetRunManager()->DefineWorldVolume(Construct());
//  Rotation takes effect upon: /run/beamOn
	G4RunManager::GetRunManager()->ReinitializeGeometry();
}
