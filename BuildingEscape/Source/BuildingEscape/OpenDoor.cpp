// Copyright Ian McCabe 2018

#include "OpenDoor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	owner = GetOwner();
	world = GetWorld();

	actorThatOpens = world->GetFirstPlayerController()->GetPawn();
}

void UOpenDoor::RotateDoor(FVector rotation)
{
	FRotator newRotation = FRotator(rotation.X, rotation.Z, rotation.Y);
	owner->SetActorRelativeRotation(newRotation);
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (pressurePlate->IsOverlappingActor(actorThatOpens))
	{
		RotateDoor(FVector(0.0f, 0.0f, openAngle));
		//lastDoorOpenTime = world->GetRealTimeSeconds();
	}
	else
	{
		RotateDoor(FVector(0.0f, 0.0f, 0.0f));
	}
	

}

