
#include "../Public/AnimGraphNode_CustomFabrik.h"
#include "Animation/AnimInstance.h"
#include "AnimNodeEditModes.h"
#include "AnimationCustomVersion.h"

#define LOCTEXT_NAMESPACE "AnimGraphNode_CustomFabrik"

UAnimGraphNode_CustomFabrik::UAnimGraphNode_CustomFabrik(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

FText UAnimGraphNode_CustomFabrik::GetControllerDescription() const
{
	return LOCTEXT("Custom Fabrik", "CUSTOM FABRIK");
}

void UAnimGraphNode_CustomFabrik::Draw(FPrimitiveDrawInterface* PDI, USkeletalMeshComponent* PreviewSkelMeshComp) const
{
	if (PreviewSkelMeshComp)
	{
		if (FAnimNode_CustomFabrik* ActiveNode = GetActiveInstanceNode<FAnimNode_CustomFabrik>(PreviewSkelMeshComp->GetAnimInstance()))
		{
			ActiveNode->ConditionalDebugDraw(PDI, PreviewSkelMeshComp);
		}
	}
}

FText UAnimGraphNode_CustomFabrik::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return GetControllerDescription();
}

void UAnimGraphNode_CustomFabrik::CopyNodeDataToPreviewNode(FAnimNode_Base* InPreviewNode)
{
	FAnimNode_CustomFabrik* Fabrik = static_cast<FAnimNode_CustomFabrik*>(InPreviewNode);

	// copies Pin values from the internal node to get data which are not compiled yet
	//Fabrik->EffectorTransform = Node.EffectorTransform;
}

FEditorModeID UAnimGraphNode_CustomFabrik::GetEditorMode() const
{
	return AnimNodeEditModes::Fabrik;
}

void UAnimGraphNode_CustomFabrik::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);

	Ar.UsingCustomVersion(FAnimationCustomVersion::GUID);

	const int32 CustomAnimVersion = Ar.CustomVer(FAnimationCustomVersion::GUID);

	if (CustomAnimVersion < FAnimationCustomVersion::ConvertIKToSupportBoneSocketTarget)
	{
		/*if (Node.EffectorTransformBone_DEPRECATED.BoneName != NAME_None)
		{
			Node.EffectorTarget = FBoneSocketTarget(Node.EffectorTransformBone_DEPRECATED.BoneName);
		}*/
	}
}

#undef LOCTEXT_NAMESPACE