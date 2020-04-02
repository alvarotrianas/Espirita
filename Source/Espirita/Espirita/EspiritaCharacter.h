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
	// Sets default values for this character's properties
	AEspiritaCharacter();
public:
	//set if the camera can move with the player
	UPROPERTY(EditAnywhere, Category = Camera)
		bool IsFixedCamera;
	//set the camera angle
	UPROPERTY(EditAnywhere, Category = Camera)
		float CameraAngle;
	//set the camera distance to the player
	UPROPERTY(EditAnywhere, Category = Camera)
		float CameraLengthToPlayer;
	//instance of camera shake
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TimeToCollet;
	//*Count the times that a timer is called*//
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TimerCalls;
	UPROPERTY(BlueprintReadWrite, Category = "Animation")
		bool bIsCasting;
	UPROPERTY(BlueprintReadWrite, Category = "Animation")
		bool bIsInteracting;
	UPROPERTY(EditAnywhere)
		float BlockDistanceFromThePlayer;


	void DoInteraction();

	UFUNCTION(BlueprintImplementableEvent)
		void StopInputWhile(float TimeToStop);

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ABlock> BlockToSpawn;
	ABlock* CurrentBlock;

	//Set posible can pic up something
	bool OnPause, CanInteract;
	//Set the current time por the pause init
	float CurrTime;
	//Set the object that implements the interect functions
	class IInteroperable* InteractObject;
	//*Game mode variable useful for all the world requirements*//
	class AEspiritaGameModeBase* GameMode;
	//* Returns CameraBoom subobject *//
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	//* Returns FollowCamera subobject *//
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }



protected:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime);

private:
	//*Overlap function, called when the actor ovelap something*//
	UFUNCTION()
		void OnOverlap(AActor* me, AActor* other);
	//*EndOverlap function, called when the actor end ovelaping something*//
	UFUNCTION()
		void EndOverlap(AActor* me, AActor* other);
	//*OnHit function, called when the actor hit something*//
	UFUNCTION()
		void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
	//* Camera boom positioning the camera behind the character *//
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;
	//* Follow camera *//
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	

};
