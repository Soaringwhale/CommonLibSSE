#pragma once


namespace RE
{
	class IXAudio2Voice
	{
	public:
		// add
		virtual void          Unk_00();        // 00
		virtual void          Unk_01();        // 01
		virtual void          Unk_02();        // 02
		virtual void          Unk_03();        // 03
		virtual void          Unk_04();        // 04
		virtual void          Unk_05();        // 05
		virtual std::int32_t  SetEffectParameters(std::uint32_t a_EffectIndex, void *a_pParameters, std::uint32_t a_ParametersByteSize, std::uint32_t a_OperationSet);  // 06
		virtual void          Unk_07();        // 07
		virtual void          Unk_08();        // 08
		virtual void          Unk_09();        // 09
		virtual void          Unk_10();        // 0A
		virtual void          Unk_11();        // 0B
		virtual void          SetVolume(float a_volume, std::uint32_t a_OperationSet);  // 0C
		virtual void          Unk_13();        // 0D
		virtual void          Unk_14();        // 0E
		virtual void          Unk_15();        // 0F
		virtual void          Unk_16();        // 10
		virtual void          Unk_17();        // 11
		virtual void          DestroyVoice();  // 12
	};
	static_assert(sizeof(IXAudio2Voice) == 0x8);
}
