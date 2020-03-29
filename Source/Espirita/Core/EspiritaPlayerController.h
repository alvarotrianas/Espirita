// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EspiritaPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ESPIRITA_API AEspiritaPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
    virtual void BeginPlay() override;
    virtual void SetupInputComponent() override;

private:
    class AEspiritaCharacter* Player = nullptr;

protected:
	UFUNCTION()
	void MoveForward(float Value);
	UFUNCTION()
	void MoveRight(float Value);
	UFUNCTION()
		void Interact();
	UFUNCTION()
		void PutBlock();
	UFUNCTION()
		void StopInteract();
	/*	UFUNCTION()
	void RestarEspiritatLevel();

*/
};
