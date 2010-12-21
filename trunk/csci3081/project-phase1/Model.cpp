#include "Model.h"
#include "Logger.h"

Model::Model() :
  logger_(0)
{
}

Model::Model(Logger* logger) :
  logger_(logger)
{

}

void Model::print(const string& string) const
{
  if (logger_ != 0)
    logger_->print(string);
}
