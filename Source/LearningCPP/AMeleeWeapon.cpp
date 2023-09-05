// Fill out your copyright notice in the Description page of Project Settings.


#include "AMeleeWeapon.h"
#include "Monster.h"
#include "Engine/DamageEvents.h"

// Sets default values
AAMeleeWeapon::AAMeleeWeapon(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AttackDamage = 1;
	Swinging = false;
	WeaponHolder = NULL;
	Mesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Mesh"));
	RootComponent = Mesh;
	ProxBox = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("ProxBox"));
	ProxBox->OnComponentBeginOverlap.AddDynamic(this, &AAMeleeWeapon::Prox);
	ProxBox->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

void AAMeleeWeapon::Prox_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// �� ���� �� �������� ����������
	if (OtherComp != OtherActor->GetRootComponent())
	{
		return;
	}
	// �������� ��������� ������ ����� ��� ������� �����,
	// �������� ��������� ������� �� ����, �
	// �������� ��������� ������ �� ������ OtherActor ������
	if (Swinging && (OtherActor != Cast<AActor>(WeaponHolder)) && !ThingsHit.Contains(OtherActor))
	{
		OtherActor->TakeDamage(AttackDamage + WeaponHolder->BaseAttackDamage, FDamageEvent(), NULL, this);
		ThingsHit.Add(OtherActor);
	}
}
void AAMeleeWeapon::Swing()
{
	ThingsHit.Empty(); // ���������� ������
	Swinging = true;
}
void AAMeleeWeapon::Rest()
{
	ThingsHit.Empty();
	Swinging = false;
}


// Called when the game starts or when spawned
void AAMeleeWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAMeleeWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

