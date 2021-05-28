// Fill out your copyright notice in the Description page of Project Settings.


#include "World_Position.h"
#include "GameFramework/Actor.h"


// Sets default values for this component's properties
UWorld_Position::UWorld_Position()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWorld_Position::BeginPlay()
{
	Super::BeginPlay();

	FString ObjectName = GetOwner()->GetName();
	// UE_LOG(LogTemp, Warning, TEXT("Object name is: %s"), *GetOwner()->GetName());
	
	FString ObjectPosition=GetOwner()->GetActorLocation().ToString();
	
	UE_LOG(LogTemp, Warning, TEXT("%s's Position is: %s"), *ObjectName, *ObjectPosition);
}


// Called every frame
void UWorld_Position::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

