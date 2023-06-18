#ifndef FLOUNDER_GAME_PARAMETERS_H
#define FLOUNDER_GAME_PARAMETERS_H

namespace flounder {

template<typename ParameterEnum, typename ValueType>
class Parameters
{

};

} // namespace flounder

enum class StringParameter
{
    minLength = 0x01,
    maxLength = 0x02,
};

struct StringParameters : public flounder::Parameters<StringParameter, unsigned int>
{
};

#endif // FLOUNDER_GAME_PARAMETERS_H
