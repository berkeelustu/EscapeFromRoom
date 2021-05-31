#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "World_Position.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UWorld_Position : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UWorld_Position();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
