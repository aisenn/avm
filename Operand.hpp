#ifndef OPERAND_HPP
#define OPERAND_HPP

template <typename T>
class Operand : public IOperand {
private:


public:
	Operand() {}
	Operand<T>(T value) {


	}
	Operand<T>(Operand const & cp) {
		*this = cp;
	}

	Operand &operator=( IOperand const &rhs ) const {
		if (this != &rhs) {

		}
		return *this;
	}

	virtual int getPrecision( void ) const override {

	}
	virtual eOperandType getType( void ) const override {

	}

	virtual IOperand const * operator+( IOperand const & rhs ) const override {

	}
	virtual IOperand const * operator-( IOperand const & rhs ) const override {

	}
	virtual IOperand const * operator*( IOperand const & rhs ) const override {

	}
	virtual IOperand const * operator/( IOperand const & rhs ) const override {

	}
	virtual IOperand const * operator%( IOperand const & rhs ) const override {

	}

	virtual std::string const & toString( void ) const override {

	}

	virtual ~Operand() {}
};

#endif //OPERAND_HPP
