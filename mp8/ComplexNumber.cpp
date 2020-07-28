#include "ComplexNumber.h"
#include "helper.h"

ComplexNumber::ComplexNumber()
{
    real_component = 0.0;
    imaginary_component = 0.0;
}

ComplexNumber::ComplexNumber(double rval_real_component, double rval_imaginary_component)
{
    real_component = rval_real_component;
    imaginary_component = rval_imaginary_component;
}

ComplexNumber::ComplexNumber( const ComplexNumber& other )
{
    this->real_component = other.get_real_component();
    this->imaginary_component = other.get_imaginary_component();
}

void ComplexNumber::set_real_component (double rval)
{
    this->real_component = rval;
}

double ComplexNumber::get_real_component() const
{
    return real_component;
}

void ComplexNumber::set_imaginary_component (double rval)
{
    this->imaginary_component = rval;
}

double ComplexNumber::get_imaginary_component() const
{
    return imaginary_component;
}

double ComplexNumber::get_magnitude() const{
    
    return sqrt(pow(real_component,2) + pow(imaginary_component,2));
}

double ComplexNumber::get_phase() const{
    
    return calculate_phase(real_component, imaginary_component);
}

ComplexNumber ComplexNumber::operator + (const ComplexNumber& arg)
{
    
    return ComplexNumber(this->real_component + arg.get_real_component(), this->imaginary_component + arg.get_imaginary_component());
}

ComplexNumber ComplexNumber::operator - (const ComplexNumber& arg)
{
    
    return ComplexNumber(this->real_component - arg.get_real_component(), this->imaginary_component - arg.get_imaginary_component());
}

ComplexNumber ComplexNumber::operator * (const ComplexNumber& arg)
{
    double realcomp = this->real_component * arg.get_real_component() - this->imaginary_component * arg.get_imaginary_component();
    double imgcomp = this->real_component * arg.get_imaginary_component() + this->imaginary_component * arg.get_real_component();
    return ComplexNumber(realcomp, imgcomp);
}

ComplexNumber ComplexNumber::operator / (const ComplexNumber& arg)
{
    double denom = pow(arg.get_real_component(),2) + pow(arg.get_imaginary_component(),2);
    double realNum = this->real_component * arg.get_real_component() + this->imaginary_component * arg.get_imaginary_component(); 
    double imgNum = this->imaginary_component * arg.get_real_component() - this->real_component * arg.get_imaginary_component();
    return ComplexNumber(realNum/denom, imgNum/denom);
}

ComplexNumber ComplexNumber::operator + (const RealNumber& arg)
{
	return ComplexNumber(this->real_component + arg.get_real_component(), this->imaginary_component);
}

ComplexNumber ComplexNumber::operator - (const RealNumber& arg)
{
    
	return ComplexNumber(this->real_component - arg.get_real_component(), this->imaginary_component);
}

ComplexNumber ComplexNumber::operator * (const RealNumber& arg)
{
    
	return ComplexNumber(this->real_component * arg.get_real_component(), this->imaginary_component * arg.get_real_component());
}

ComplexNumber ComplexNumber::operator / (const RealNumber& arg)
{
    
	return ComplexNumber(this->real_component / arg.get_real_component(), this->imaginary_component / arg.get_real_component());
}

ComplexNumber ComplexNumber::operator + (const ImaginaryNumber& arg){
    
	return ComplexNumber(this->real_component, this->imaginary_component + arg.get_imaginary_component());
}

ComplexNumber ComplexNumber::operator - (const ImaginaryNumber& arg)
{
    
	return ComplexNumber(this->real_component, this->imaginary_component - arg.get_imaginary_component());
}

ComplexNumber ComplexNumber::operator * (const ImaginaryNumber& arg)
{
    
	return ComplexNumber(-1*this->imaginary_component*arg.get_imaginary_component(), this->real_component * arg.get_imaginary_component());
}

ComplexNumber ComplexNumber::operator / (const ImaginaryNumber& arg)
{
    
	return ComplexNumber(this->real_component / arg.get_imaginary_component(), this->imaginary_component / arg.get_imaginary_component());
}

string ComplexNumber::to_String(){
    /* Do not modify */
    stringstream my_output;
    if (imaginary_component > 0)
        my_output << std::setprecision(3) << real_component << " + " << imaginary_component << 'i';
    else if (imaginary_component < 0)
        my_output << std::setprecision(3) << real_component << " - " << abs(imaginary_component) << 'i';
    else
        my_output << std::setprecision(3) << real_component;
    
    return my_output.str();
}