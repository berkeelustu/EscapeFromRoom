#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UOpenDoor();
	

protected:
	
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);

private:
float InitialYaw;
float CurrentYaw;

float DoorLastOpened;

UPROPERTY(EditAnywhere)
float DoorCloseDelay = .5f;

UPROPERTY(EditAnywhere)
float TargetYaw=90.f;

UPROPERTY(EditAnywhere)
ATriggerVolume* PressureBox;

UPROPERTY(EditAnywhere)
AActor* ActorThatOpens;

UPROPERTY(EditAnywhere)
float DoorOpenSpeed=.8f;

UPROPERTY(EditAnywhere)
float DoorCloseSpeed=2.f;
};
