// Copyright Ian McCabe 2018

#include "Grabber.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FString objectName = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s reporting for duty!"), *objectName);
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// get the player viewpoint
	FVector playerViewLocation;
	FRotator playerViewRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT playerViewLocation, 
		OUT playerViewRotation
	);

	//UE_LOG(LogTemp, Warning, TEXT("Location: %s  Rotation: %s "), playerViewLocation, playerViewRotation);

	// raycast out the players viewport
	// see what we hit.
}

