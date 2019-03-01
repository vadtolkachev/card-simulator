#pragma once
#include "IKCCompositionObserver.hpp"
#include "KCBoolCommand.hpp"
#include "KCLongCommand.hpp"
#include "KCStringCommand.hpp"
#include "KCIdentifiable.hpp"
#include "KCPoint.hpp"

enum KCCardAligment
{
    KCCardAligmentVertical,
    KCCardAligmentHorizontal
};

enum KCCardSuit
{
	KCCardSuit_Diamonds,
	KCCardSuit_Clubs,
	KCCardSuit_Hearts,
	KCCardSuit__Spades
};

enum KCCardRank
{
    KCCardRank_Two = 2,
    KCCardRank_Three = 3,
	KCCardRank_Four = 4,
	KCCardRank_Five = 5,
	KCCardRank_Six = 6,
	KCCardRank_Seven = 7,
	KCCardRank_Eignt = 8,
	KCCardRank_Nine = 9,
	KCCardRank_Ten = 10,
	KCCardRank_Jack = 11,
	KCCardRank_Queen = 12,
	KCCardRank_King = 13,
	KCCardRank_Ace = 14
};


class KCCard : virtual public IKCDriven, virtual public KCIdentifiable
{
public:
    
    KCCard(KCCardSuit suit, KCCardRank rank, IKCCompositionObserver* observer);
    ~KCCard();
    
	bool							isHidden() const;
	KCCardSuit						getSuit() const;
	KCCardRank						getRank() const;
	KCCardAligment					getAligment() const;
	KCPoint							getPosition() const;
	virtual IKCCompositionObserver*	getObserver() const;
	virtual std::string				getID() const;

    void			setHidden(bool hidden);
    void			setAligment(KCCardAligment aligment);
	void			setPosition(const KCPoint& position);
	virtual void	setObserver(IKCCompositionObserver* observer);
	virtual void	setID(std::string ID);

private:
	KCCard();
	KCCard(const KCCard& c);

	bool						m_hidden;
	KCCardSuit					m_suit;
	KCCardRank					m_rank;
	KCCardAligment				m_aligment;
	KCPoint						m_position;
	IKCCompositionObserver*		m_observer;
};
