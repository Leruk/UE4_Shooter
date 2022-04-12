#pragma once


class AnimUtilities {
public:
	template <typename T>
	static T* FindNotifyByClass(UAnimMontage* Animation)
	{
		if (!Animation) return nullptr;

		const auto NotifyEvents = Animation->Notifies;

		for (auto NotifyEvent : NotifyEvents)
		{
			auto CurrentEquipNotify = Cast<T>(NotifyEvent.Notify);

			if (CurrentEquipNotify)
			{
				return CurrentEquipNotify;
			}
		}
		return nullptr;
	}
};