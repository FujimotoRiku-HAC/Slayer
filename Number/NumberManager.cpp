#include "NumberManager.h"
#include "Number.h"

NumberManager::~NumberManager(){
	Clear();
}

void NumberManager::Add(Number* number){
	m_Numbers.push_back(number);
}

void NumberManager::Update(float delta_time){
	std::ranges::for_each(m_Numbers,
		[delta_time](Number* number) {number->Update(delta_time); });
}

void NumberManager::Draw() const{
	std::ranges::for_each(m_Numbers,
		[](Number* number) {number->Draw(); });
}

void NumberManager::Remove(){
	m_Numbers.remove_if(
		[](Number* number)->bool {
			if (number->IsDead()) {
				delete number;
				return true;
			}
			return false;
		}
	);
}

void NumberManager::Clear(){
	std::ranges::for_each(m_Numbers,
		[](Number* number) {delete number; });
	m_Numbers.clear();
}
