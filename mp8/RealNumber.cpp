#include "RealNumber.h"
#include "helper.h"

RealNumber::RealNumber()
{
    real_component = 0.0;
    number_type = REAL;
}

RealNumber::RealNumber(double rval)
{
    real_component = rval;
}

RealNumber::RealNumber( const RealNumber& other )
{
    this->real_component = other.get_real_component();
}

void RealNumber::set_real_component (double rval)
{
    real_component = rval;
}

double RealNumber::get_real_component() const
{
    return real_component;
}

double RealNumber::get_magnitude() const{
    return abs(real_component);
}

double RealNumber::get_phase() const{
    return calculate_phase(real_component, 0);
}

RealNumber RealNumber::operator + (const RealNumber& arg)
{
    return RealNumber(this->real_component + arg.real_component);
}

RealNumber RealNumber::operator - (const RealNumber& arg)
{
    return RealNumber(this->real_component - arg.real_component);
}

RealNumber RealNumber::operator * (const RealNumber& arg)
{
    return RealNumber(this->real_component * arg.real_component);
}

RealNumber RealNumber::operator / (const RealNumber& arg)
{
    return RealNumber(this->real_component / arg.get_real_component());
}

ComplexNumber RealNumber::operator + (const ImaginaryNumber& arg){
    return ComplexNumber(this->real_component, arg.get_imaginary_component());
}

ComplexNumber RealNumber::operator - (const ImaginaryNumber& arg){
	return ComplexNumber(this->real_component, arg.get_imaginary_component());
}

ImaginaryNumber RealNumber::operator * (const ImaginaryNumber& arg){
	return ImaginaryNumber(this->real_component * arg.get_imaginary_component());
}

ImaginaryNumber RealNumber::operator / (const ImaginaryNumber& arg){
	return ImaginaryNumber(this->real_component / arg.get_imaginary_component());
}

ComplexNumber RealNumber::operator + (const ComplexNumber& arg){
	return ComplexNumber(this->real_component + arg.get_real_component(), arg.get_imaginary_component());
}

ComplexNumber RealNumber::operator - (const ComplexNumber& arg){
	return ComplexNumber(this->real_component - arg.get_real_component(), arg.get_imaginary_component());
}

ComplexNumber RealNumber::operator * (const ComplexNumber& arg){
	return ComplexNumber(this->real_component * arg.get_real_component(), this->real_component * arg.get_imaginary_component());
}

ComplexNumber RealNumber::operator / (const ComplexNumber& arg){
    return ComplexNumber(this->real_component / arg.get_real_component(), this->real_component / arg.get_imaginary_component());
}

string RealNumber::to_String(){
    /* Do not modify */
    stringstream my_output;
    my_output << std::setprecision(3) << real_component;
    return my_output.str();
}