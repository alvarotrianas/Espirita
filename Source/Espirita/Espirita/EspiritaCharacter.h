// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Espirita/Mechanics/Block/Block.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EspiritaCharacter.generated.h"

UCLASS()
class ESPIRITA_API AEspiritaCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AEspiritaCharacter();
public:
	UPROPERTY(EditAnywhere, Category = Camera)
		bool IsFixedCamera;
	UPROPERTY(EditAnywhere, Category = Camera)
		float CameraAngle;
	UPROPERTY(EditAnywhere, Category = Camera)
		float CameraLengthToPlayer;
	UPROPERTY(BlueprintReadWrite, Category = "Animation")
		bool bIsCasting;
	UPROPERTY(BlueprintReadWrite, Category = "Animation")
		bool bIsInteracting;
	UPROPERTY(BlueprintReadOnly, Category = "Character Movement: Running")
		bool IsRunning;
	UPROPERTY(EditAnywhere)
		float BlockDistanceFromThePlayer;
	UPROPERTY(Category = "Character Movement: Running", EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", UIMin = "0"))
		float RunSpeedMultiplier;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	UFUNCTION(BlueprintImplementableEvent)
		void InvokeBlock();

	UFUNCTION(BlueprintCallable)
		void PutBlock();

	UFUNCTION(BlueprintCallable)
		void EndGame();

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ABlock> BlockToSpawn;

	void DoInteraction();
	void TryStartRun();
	void TryStopRun();

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime);
private:
	ABlock* CurrentBlock;
	UCharacterMovementComponent* Movement;
	class IInteroperable* InteractObject;
	class AEspiritaGameModeBase* GameMode;
	bool CanInteract;
	float BaseMovementSpeed;

	UFUNCTION()
		void OnOverlap(AActor* me, AActor* other);
	UFUNCTION()
		void EndOverlap(AActor* me, AActor* other);
};
