// Copyright Ian McCabe 2018

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void RotateDoor(FVector rotation);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	AActor* owner;
	UWorld* world;

	AActor* actorThatOpens;
	bool isDoorOpen;

	UPROPERTY(EditAnywhere)
	float openAngle = -90.0f;

	UPROPERTY(EditAnywhere)
	float doorCloseDelay;

	float lastDoorOpenTime;	

	UPROPERTY(EditAnywhere)
	ATriggerVolume* pressurePlate;
};
