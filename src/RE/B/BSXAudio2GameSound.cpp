
#include "RE/B/BSXAudio2GameSound.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	
	void BSXAudio2GameSound::OutputModelChangedImpl()
	{
		using func_t = decltype(&BSXAudio2GameSound::OutputModelChangedImpl);
		REL::Relocation<func_t> func{ Offset::BSXAudio2GameSound::OutputModelChangedImpl };
		return func (this);
	}

	bool BSXAudio2GameSound::SyncOpen()
	{
		using func_t = decltype(&BSXAudio2GameSound::SyncOpen);
		REL::Relocation<func_t> func{ Offset::BSXAudio2GameSound::SyncOpen };
		return func (this);
	}

  bool BSXAudio2GameSound::StartAsyncOpen()
	{
		using func_t = decltype(&BSXAudio2GameSound::StartAsyncOpen);
		REL::Relocation<func_t> func{ Offset::BSXAudio2GameSound::StartAsyncOpen };
		return func (this);
	}

  bool BSXAudio2GameSound::TestAsyncOpenReady()
	{
		using func_t = decltype(&BSXAudio2GameSound::TestAsyncOpenReady);
		REL::Relocation<func_t> func{ Offset::BSXAudio2GameSound::TestAsyncOpenReady };
		return func (this);
	}

  bool BSXAudio2GameSound::FinishAsyncOpen()
	{
		using func_t = decltype(&BSXAudio2GameSound::FinishAsyncOpen);
		REL::Relocation<func_t> func{ Offset::BSXAudio2GameSound::FinishAsyncOpen };
		return func (this);
	}

  bool BSXAudio2GameSound::HandleExternalOpen()
	{
		using func_t = decltype(&BSXAudio2GameSound::HandleExternalOpen);
		REL::Relocation<func_t> func{ Offset::BSXAudio2GameSound::HandleExternalOpen };
		return func (this);
	}

  bool BSXAudio2GameSound::Prepare()
	{
		using func_t = decltype(&BSXAudio2GameSound::Prepare);
		REL::Relocation<func_t> func{ Offset::BSXAudio2GameSound::Prepare };
		return func (this);
	}

	void BSXAudio2GameSound::Copy(BSGameSound *other, bool a3)
	{
		using func_t = decltype(&BSXAudio2GameSound::Copy);
		REL::Relocation<func_t> func{ Offset::BSXAudio2GameSound::Copy };
		return func (this, other, a3);
	}

	void BSXAudio2GameSound::UpdateEmitterPosition()
	{
		using func_t = decltype(&BSXAudio2GameSound::UpdateEmitterPosition);
		REL::Relocation<func_t> func{ Offset::BSXAudio2GameSound::UpdateEmitterPosition };
		return func (this);
	}

	bool BSXAudio2GameSound::Update()
	{
		using func_t = decltype(&BSXAudio2GameSound::Update);
		REL::Relocation<func_t> func{ Offset::BSXAudio2GameSound::Update };
		return func (this);
	}

	void BSXAudio2GameSound::SetEmitterPositionImpl(const NiPoint3 &pos)
	{
		using func_t = decltype(&BSXAudio2GameSound::SetEmitterPositionImpl);
		REL::Relocation<func_t> func{ Offset::BSXAudio2GameSound::SetEmitterPositionImpl };
		return func (this, pos);
	}

	void BSXAudio2GameSound::GetEmitterPositionImpl(const NiPoint3 &outPos)
	{
		using func_t = decltype(&BSXAudio2GameSound::GetEmitterPositionImpl);
		REL::Relocation<func_t> func{ Offset::BSXAudio2GameSound::GetEmitterPositionImpl };
		return func (this, outPos);
	}

	void BSXAudio2GameSound::DoApplyFrequency()
	{
		using func_t = decltype(&BSXAudio2GameSound::DoApplyFrequency);
		REL::Relocation<func_t> func{ Offset::BSXAudio2GameSound::DoApplyFrequency };
		return func (this);
	}

	void BSXAudio2GameSound::SeekInSamples(uint32_t a2)
	{
		using func_t = decltype(&BSXAudio2GameSound::SeekInSamples);
		REL::Relocation<func_t> func{ Offset::BSXAudio2GameSound::SeekInSamples };
		return func (this, a2);
	}

	void BSXAudio2GameSound::PlayImpl()
	{
		using func_t = decltype(&BSXAudio2GameSound::PlayImpl);
		REL::Relocation<func_t> func{ Offset::BSXAudio2GameSound::PlayImpl };
		return func (this);
	}

	void BSXAudio2GameSound::PauseImpl()
	{
		using func_t = decltype(&BSXAudio2GameSound::PauseImpl);
		REL::Relocation<func_t> func{ Offset::BSXAudio2GameSound::PauseImpl };
		return func (this);
	}

	void BSXAudio2GameSound::StopImpl(bool a2)
	{
		using func_t = decltype(&BSXAudio2GameSound::StopImpl);
		REL::Relocation<func_t> func{ Offset::BSXAudio2GameSound::StopImpl };
		return func (this, a2);
	}

	void BSXAudio2GameSound::SetVolumeImpl()
	{
		using func_t = decltype(&BSXAudio2GameSound::SetVolumeImpl);
		REL::Relocation<func_t> func{ Offset::BSXAudio2GameSound::SetVolumeImpl };
		return func (this);
	}
}
