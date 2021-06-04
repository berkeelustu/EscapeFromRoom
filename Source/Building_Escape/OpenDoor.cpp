// Fill out your copyright notice in the Description page of Project Settings.
#include "OpenDoor.h"
#include "Components/PrimitiveComponent.h"
#include "Components/AudioComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
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
	
	FindAudioComponent();
}
void UOpenDoor::FindAudioComponent()
{
	AudioComponent=GetOwner()->FindComponentByClass<UAudioComponent>();
}
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

if(TotalMassOfActors()>50.f)
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
OpenDoorSound = false;
    if (!AudioComponent) {return;}
	if(!OpenDoorSound)
	{
		AudioComponent->Play();
		OpenDoorSound=true;
	}
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	CurrentYaw =FMath::FInterpTo(CurrentYaw,InitialYaw,DeltaTime, DoorCloseSpeed);
	FRotator DoorRotation=GetOwner()->GetActorRotation();
	DoorRotation.Yaw=CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);
	for(int32 i =0;i < 2;i++)
	CloseDoorSound = false;
	if (!AudioComponent) {return;}
	if(!CloseDoorSound)
	{
		AudioComponent->Play();
		CloseDoorSound=true;
	}
}

float UOpenDoor::TotalMassOfActors() const
{
	float TotalMass = 0.f;
	TArray <AActor*> OverlappingActors;
	PressureBox->GetOverlappingActors(OUT OverlappingActors);
	for(AActor* Actor :OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp,Warning, TEXT("%s on the Pressure Box."), *Actor->GetName());		
	}

	return TotalMass;
}

