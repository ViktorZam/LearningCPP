// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Avatar.h"
#include "MyHUD.h"
#include "Kismet/GameplayStatics.h"
#include "PickupItem.generated.h"

UCLASS()
class LEARNINGCPP_API APickupItem : public AActor
{
	GENERATED_BODY()

public:
	// ��� ��������, ������� �� �����������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	FString Name;
	// ��� ����� �� �����������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	int32 Quantity;
	// �����, � ������� �� �������������, ��� ��������� �������
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Item)
	USphereComponent* ProxSphere;
		// ����� ��������
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Item)
	UStaticMeshComponent* Mesh;
	// ������, ������� ������������ ������ � ���������� ������������/�� �����������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	UTexture2D* Icon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	UClass* Spell;

	// ����� ���-�� �������� � ProxSphere, ��� ������� �����������
	UFUNCTION(BlueprintNativeEvent, Category = Collision)
	void Prox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);






public:	
	// Sets default values for this actor's properties
	APickupItem(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
