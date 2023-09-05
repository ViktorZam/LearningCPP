// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC.h"

// Sets default values


ANPC::ANPC(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	ProxSphere = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("Proximity Sphere"));
	
	ProxSphere->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	ProxSphere->SetSphereRadius(90.f);
	// ��� ��� ������� ANPC::Prox(), ����� ��� ����� �����������
	// ������������ � ������ �������.
	ProxSphere->OnComponentBeginOverlap.AddDynamic(this, &ANPC::Prox);
	//NpcMessage = "Hi, I'm Owen";// ��������� �� ���������, ����� ���� ���������������
	// � blueprint
}
// �������� ��������! ���� ��� ANPC::Prox() � ���� ��������� � ������������ �����,
// ������ ��� ��� ����� ANPC::Prox_Implementation.
void ANPC::Prox_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
								int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// ���� �����, � ������� ��������� �����������, ��� �� �����,
// �� ������ ������ ��������� �� �������
	if (Cast<AAvatar>(OtherActor) == nullptr)
	{
		return;
	}
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	if (PController)
	{
		AMyHUD* hud = Cast<AMyHUD>(PController->GetHUD());
		hud->addMessage(Message(NpcMessage, 5.f, FColor::White, Face));
	}

}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

