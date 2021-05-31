#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "OpenDoor.h"
#include "GameFramework/Actor.h"

UOpenDoor::UOpenDoor()
{
	
	PrimaryComponentTick.bCanEverTick = true;
}


void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	TargetYaw += InitialYaw;

	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();

}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

if(PressureBox->IsOverlappingActor(ActorThatOpens))
{
OpenDoor(DeltaTime);
DoorLastOpened = GetWorld()->GetTimeSeconds();
}
else
{
	if(GetWorld()->GetTimeSeconds() - DoorLastOpened > DoorCloseDelay)
	{
		CloseDoor(DeltaTime);
	}

}
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
CurrentYaw = FMath::FInterpTo(CurrentYaw,TargetYaw,DeltaTime, DoorOpenSpeed);
FRotator DoorRotation=GetOwner()->GetActorRotation();
DoorRotation.Yaw = CurrentYaw;
GetOwner()->SetActorRotation(DoorRotation);
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	CurrentYaw =FMath::FInterpTo(CurrentYaw,InitialYaw,DeltaTime, DoorCloseSpeed);
	FRotator DoorRotation=GetOwner()->GetActorRotation();
	DoorRotation.Yaw=CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);
}
