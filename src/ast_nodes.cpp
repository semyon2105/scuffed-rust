#include <utility>
#include <parse.h>

#include "ast_nodes.h"

using namespace Funlang::AST;

Program::Program(std::vector<std::unique_ptr<Function>> functions)
    : functions_{std::move(functions)}
{
}

const std::vector<std::unique_ptr<Function>>& Program::functions() const
{
    return functions_;
}

Function::Function(std::string name,
                   std::vector<std::unique_ptr<Parameter>> params,
                   std::string return_type,
                   std::unique_ptr<Block> body)
    : name_{std::move(name)},
      params_{std::move(params)},
      return_type_{std::move(return_type)},
      body_{std::move(body)}
{
}

const std::string& Function::name() const
{
    return name_;
}

const std::vector<std::unique_ptr<Parameter>>& Function::parameters() const
{
    return params_;
}

const std::string& Function::return_type() const
{
    return return_type_;
}

Block* Function::body() const
{
    return body_.get();
}

Parameter::Parameter(std::string name, std::string type_name)
        : name_{std::move(name)}, type_name_{std::move(type_name)}
{
}

const std::string& Parameter::name() const
{
    return name_;
}

const std::string& Parameter::type_name() const
{
    return type_name_;
}

Block::Block(std::vector<std::unique_ptr<Expression>> exprs)
    : exprs{std::move(exprs)}
{
}

const std::vector<std::unique_ptr<Expression>>& Block::expressions() const
{
    return exprs;
}

const std::string& Expression::type() const
{
    const static std::string test_type = "void";
    return test_type;
}

Definition::Definition(
        std::string var_name,
        std::string var_type,
        std::unique_ptr<Expression> expr)
    : var_name_{std::move(var_name)}, var_type_{std::move(var_type)}, expr{std::move(expr)}
{
}

const std::string& Definition::var_name() const
{
    return var_name_;
}

const std::string& Definition::var_type() const
{
    return var_type_;
}

Expression* Definition::expression() const
{
    return expr.get();
}

Assignment::Assignment(std::string variable_name, std::unique_ptr<Expression> expression)
    : var_name{std::move(variable_name)}, expr{std::move(expression)}
{
}

const std::string& Assignment::variable_name() const
{
    return var_name;
}

Expression* Assignment::expression() const
{
    return expr.get();
}

BinaryOperation::BinaryOperation(
        std::unique_ptr<Expression> lhs,
        std::unique_ptr<BinaryOperationRest> rest)
    : lhs_{std::move(lhs)}, rest_{std::move(rest)}
{
}

Expression* BinaryOperation::lhs() const
{
    return lhs_.get();
}

BinaryOperationRest* BinaryOperation::rest() const
{
    return rest_.get();
}

BinaryOperation::Kind BinaryOperation::from_token_kind(const Token::Kind& kind)
{
    switch (kind) {
        case (Token::Kind)'+': return Kind::Add;
        case (Token::Kind)'-': return Kind::Sub;
        case (Token::Kind)'*': return Kind::Mul;
        case (Token::Kind)'/': return Kind::Div;
        case (Token::Kind)'<': return Kind::Less;
        case (Token::Kind)'>': return Kind::Greater;
        case Token::EQ: return Kind::Equal;
        case Token::NEQ: return Kind::NotEq;
        case Token::LE: return Kind::LeEq;
        case Token::GE: return Kind::GrEq;
        default: break;
    }
    return static_cast<Kind>(-1);
}

const std::map<BinaryOperation::Kind, const std::string>
BinaryOperation::kind_strings {
        { Kind::Add, "Add" },
        { Kind::Sub, "Sub" },
        { Kind::Mul, "Mul" },
        { Kind::Div, "Div" },
        { Kind::Less, "Less" },
        { Kind::Greater, "Greater" },
        { Kind::Equal, "Equal" },
        { Kind::NotEq, "NotEq" },
        { Kind::LeEq, "LeEq" },
        { Kind::GrEq, "GrEq" }
};

BinaryOperationRest::BinaryOperationRest(
        BinaryOperation::Kind kind,
        std::unique_ptr<Expression> rhs,
        std::unique_ptr<BinaryOperationRest> rest)
    : kind_{kind}, rhs_{std::move(rhs)}, rest_{std::move(rest)}
{
}

BinaryOperation::Kind BinaryOperationRest::kind() const
{
    return kind_;
}

Expression* BinaryOperationRest::rhs() const
{
    return rhs_.get();
}

BinaryOperationRest*  BinaryOperationRest::rest() const
{
    return rest_.get();
}

UnaryOperation::UnaryOperation(Kind kind, std::unique_ptr<Expression> expr)
        : kind_{kind}, expr{std::move(expr)}
{
}

const std::map<UnaryOperation::Kind, const std::string>
UnaryOperation::kind_strings {
        { Kind::Minus, "Minus" },
        { Kind::Not, "Not" }
};

UnaryOperation::Kind UnaryOperation::kind() const
{
    return kind_;
}

Expression* UnaryOperation::expression() const
{
    return expr.get();
}


IfExpr::IfExpr(std::unique_ptr<Expression> condition, std::unique_ptr<Block> body)
    : cond{std::move(condition)}, body_{std::move(body)}
{
}

Expression* IfExpr::condition() const
{
    return cond.get();
}

Block* IfExpr::body() const
{
    return body_.get();
}

WhileExpr::WhileExpr(std::unique_ptr<Expression> condition, std::unique_ptr<Block> body)
        : cond{std::move(condition)}, body_{std::move(body)}
{
}

Expression* WhileExpr::condition() const
{
    return cond.get();
}

Block* WhileExpr::body() const
{
    return body_.get();
}

FunctionCall::FunctionCall(
        std::string func_name,
        std::vector<std::unique_ptr<Expression>> args)
    : func_name{std::move(func_name)}, args{std::move(args)}
{
}

const std::string& FunctionCall::function_name() const
{
    return func_name;
}

const std::vector<std::unique_ptr<Expression>>&
FunctionCall::arguments() const
{
    return args;
}

Variable::Variable(std::string name)
    : name_{std::move(name)}
{
}

const std::string& Variable::name() const
{
    return name_;
}

BoolValue::BoolValue(bool value)
    : value{value}
{
}

const std::string& BoolValue::type() const
{
    static const std::string type = "bool";
    return type;
}

IntValue::IntValue(int value)
        : value{value}
{
}

const std::string& IntValue::type() const
{
    static const std::string type = "int";
    return type;
}

FloatValue::FloatValue(double value)
        : value{value}
{
}

const std::string& FloatValue::type() const
{
    static const std::string type = "float";
    return type;
}

NullValue::NullValue()
{
}

const std::string& NullValue::type() const
{
    static const std::string type = "void";
    return type;
}

void Program::accept(Visitor& v) { v.accept(*this); }
void Function::accept(Visitor& v) { v.accept(*this); }
void Parameter::accept(Visitor& v) { v.accept(*this); }
void Block::accept(Visitor& v) { v.accept(*this); }
void Definition::accept(Visitor& v) { v.accept(*this); }
void Assignment::accept(Visitor& v) { v.accept(*this); }
void BinaryOperation::accept(Visitor& v) { v.accept(*this); }
void BinaryOperationRest::accept(Visitor& v) { v.accept(*this); }
void UnaryOperation::accept(Visitor& v) { v.accept(*this); }
void IfExpr::accept(Visitor& v) { v.accept(*this); }
void WhileExpr::accept(Visitor& v) { v.accept(*this); }
void FunctionCall::accept(Visitor& v) { v.accept(*this); }
void Variable::accept(Visitor& v) { v.accept(*this); }
void BoolValue::accept(Visitor& v) { v.accept(*this); }
void IntValue::accept(Visitor& v) { v.accept(*this); }
void FloatValue::accept(Visitor& v) { v.accept(*this); }
void NullValue::accept(Visitor& v) { v.accept(*this); }