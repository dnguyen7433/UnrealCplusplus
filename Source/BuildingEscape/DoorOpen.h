// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h "
#include "DoorOpen.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UDoorOpen : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorOpen();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenTheDoor();
	void CloseTheDoor();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	

private:
	// UPROPERTY is a macro which do cut-and-paste a specific specifier. 
	//The syntax doesn't need a semicolon
	UPROPERTY(EditAnywhere)
	float OpenAngle = -0.000292;
	UPROPERTY(EditAnywhere)
	float CloseAngle = 89.89f;

	UPROPERTY(EditAnywhere) 

	// A part of the syntax of UPROPERTY
	ATriggerVolume* PressurePlate = nullptr; 

	UPROPERTY(EditAnyWhere)
	float DoorCloseDelay = 0.01f;
	float LastDoorOpenTime;

	// The Owning door 
	AActor* Owner; 

	// Return the total mass on the pressure plate that allows the door to open
	float GetTotalMassOfActorOnPressurePlate(); 
};
