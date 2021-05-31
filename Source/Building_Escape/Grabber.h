#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UGrabber();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	
	virtual void BeginPlay() override;
		
private:

float Reach= 200.f;
UPhysicsHandleComponent* PhysicsHandle= nullptr;
UInputComponent* InputComponent= nullptr;

void Grab();
void Release();
void FindPhysicsHandle ();
void SetUpInputComponent ();

FHitResult GetFirstPhysicsBodyInReach() const;
};
