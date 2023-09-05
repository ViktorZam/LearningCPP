// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

class USphereComponent;

UCLASS()
class LEARNINGCPP_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet(const FObjectInitializer& ObjectInitializer);
	// —колько урона наносит пул€.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties)
	float Damage;
	// ¬идима€ сетка Ц Meshдл€ компонента, чтобы мы могли
	// стрел€ющий объект
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Collision)
	UStaticMeshComponent* Mesh;
		// сфера, с которой вы сталкиваетесь, чтобы нанести урон
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Collision)
	USphereComponent * ProxSphere;
	UFUNCTION(BlueprintNativeEvent, Category = Collision)
	void Prox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
