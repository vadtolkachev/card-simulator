#include "KCPlayer.hpp"
#include "KCStringCommand.hpp"

KCPlayer::KCPlayer(std::string ID, IKCCompositionObserver* observer) : KCCardsOwner(ID, observer), KCIdentifiable(ID) {}

void KCPlayer::propertyChanged(std::shared_ptr<KCCommand> command)
{
	KCBoolCommand* boolCommand = dynamic_cast<KCBoolCommand *>(command.get());
	printf("PLAYER: card has been changed %d\n", boolCommand->getNewValue());
	getObserver()->propertyChanged(command);
}