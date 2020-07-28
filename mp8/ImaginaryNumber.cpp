#include "ImaginaryNumber.h"
#include "helper.h"

ImaginaryNumber::ImaginaryNumber()
{
    imaginary_component = 0.0;
}

ImaginaryNumber::ImaginaryNumber(double rval)
{
    imaginary_component = rval;
}

ImaginaryNumber::ImaginaryNumber( const ImaginaryNumber& other )
{
    this->imaginary_component = other.get_imaginary_component();
}

void ImaginaryNumber::set_imaginary_component (double rval)
{
    this->imaginary_component = rval;
}

double ImaginaryNumber::get_imaginary_component() const
{
    return imaginary_component;
}

//Getter function for magnitude
double ImaginaryNumber::get_magnitude() const{
    return abs(imaginary_component);
}

//Getter function for phase
double ImaginaryNumber::get_phase() const{
    
    return calculate_phase(0, imaginary_component);
}

//Operator Overload
ImaginaryNumber ImaginaryNumber::operator + (const ImaginaryNumber& arg)
{
    
    return ImaginaryNumber(this->imaginary_component + arg.get_imaginary_component());
}

ImaginaryNumber ImaginaryNumber::operator - (const ImaginaryNumber& arg)
{
    
    return ImaginaryNumber(this->imaginary_component - arg.get_imaginary_component());
}

RealNumber ImaginaryNumber::operator * (const ImaginaryNumber& arg)
{
    return RealNumber(0.0);
}

RealNumber ImaginaryNumber::operator / (const ImaginaryNumber& arg)
{
    
    return RealNumber(0.0);
}

ComplexNumber ImaginaryNumber::operator + (const RealNumber& arg)
{
    
    return ComplexNumber(arg.get_real_component(), this->imaginary_component);
}

ComplexNumber ImaginaryNumber::operator - (const RealNumber& arg)
{
    
    return ComplexNumber(arg.get_real_component(), this->imaginary_component);
}

ImaginaryNumber ImaginaryNumber::operator * (const RealNumber& arg)
{
    
    return ImaginaryNumber(arg.get_real_component() * this->imaginary_component);
}

ImaginaryNumber ImaginaryNumber::operator / (const RealNumber& arg)
{
    
    return ImaginaryNumber(arg.get_real_component() / this->imaginary_component);
}

ComplexNumber ImaginaryNumber::operator + (const ComplexNumber& arg)
{
    
    return ComplexNumber(arg.get_real_component(), this->imaginary_component + arg.get_imaginary_component());
}

ComplexNumber ImaginaryNumber::operator - (const ComplexNumber& arg)
{
    
    return ComplexNumber(arg.get_real_component(), this->imaginary_component - arg.get_imaginary_component());
}

ComplexNumber ImaginaryNumber::operator * (const ComplexNumber& arg)
{
    
    return ComplexNumber(arg.get_imaginary_component() * this->imaginary_component, arg.get_real_component() * this->imaginary_component);
}

ComplexNumber ImaginaryNumber::operator / (const ComplexNumber& arg)
{
    
    return ComplexNumber(arg.get_imaginary_component() / this->imaginary_component, -1*arg.get_real_component() / this->imaginary_component);
}

string ImaginaryNumber::to_String(){
    /* Do not modify */
    stringstream my_output;
    my_output << std::setprecision(3) << imaginary_component << 'i';
    return my_output.str();
}