// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"
#include "Avatar.h"
#include "MyHUD.h"
#include "NPC.generated.h"

UCLASS()
class LEARNINGCPP_API ANPC : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPC(const FObjectInitializer& ObjectInitializer);
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision)
	USphereComponent* ProxSphere;
	// Это сообщение NPC, которое он должен сказать нам.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NPCMessage)
	FString NpcMessage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NPCMessage)
	UTexture2D* Face;
	// Когда вы создаёте blueptint из этого класса, вы хотите, чтобы вы могли
	// редактировать это сообщение в blueprint,
	// вот почему у нас есть
	// свойства EditAnywhere и BlueprintReadWrite
	UFUNCTION(BlueprintNativeEvent, Category = "Collision")
	void Prox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
				int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
