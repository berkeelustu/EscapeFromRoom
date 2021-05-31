#include "World_Position.h"
#include "GameFramework/Actor.h"


UWorld_Position::UWorld_Position()
{
	PrimaryComponentTick.bCanEverTick = true;
}



void UWorld_Position::BeginPlay()
{
	Super::BeginPlay();

	FString ObjectName = GetOwner()->GetName();
	// UE_LOG(LogTemp, Warning, TEXT("Object name is: %s"), *GetOwner()->GetName());
	
	FString ObjectPosition=GetOwner()->GetActorLocation().ToString();
	
	UE_LOG(LogTemp, Warning, TEXT("%s's Position is: %s"), *ObjectName, *ObjectPosition);
}

void UWorld_Position::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

