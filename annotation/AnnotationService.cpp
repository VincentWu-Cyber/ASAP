#include "AnnotationService.h"
#include "AnnotationList.h"
#include "XmlRepository.h"
#include "NDPARepository.h"

AnnotationService::AnnotationService() :
  _list(NULL),
  _repo(NULL)
{
  _list = new AnnotationList();
}

AnnotationService::~AnnotationService() {
  if (_repo) {
    delete _repo;
    _repo = NULL;
  }
  if (_list) {
    delete _list;
    _list = NULL;
  }
}

AnnotationList* AnnotationService::getList() const {
  return _list;
}

Repository* AnnotationService::getRepository() const {
  return _repo;
}
void AnnotationService::setRepositoryFromSourceFile(const std::string& source) {
  if (_repo) {
    delete _repo;
  }
  if (source.rfind(std::string(".xml")) != source.npos) {
    _repo = new XmlRepository(_list);
    _repo->setSource(source);
  }
  else if (source.rfind(std::string(".ndpa")) != source.npos) {
    _repo = new NDPARepository(_list);
    _repo->setSource(source);
  }
}

bool AnnotationService::load() {
  if (_repo) {
    return _repo->load();
  }
  else {
    return false;
  }
}

bool AnnotationService::save() {
  if (_repo) {
    return _repo->save();
  }
  else {
    return false;
  }
}