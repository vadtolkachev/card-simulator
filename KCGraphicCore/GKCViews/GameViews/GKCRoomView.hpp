#pragma once
#include "GKCTableView.hpp"
#include "GKCPlayerView.hpp"
#include "GKCDragAndDropController.hpp"
#include "KCRoom.hpp"
#include "GKCRoomView.hpp"
#include "GKCMenuItem.hpp"

#include <set>


//class GKCMenuItem;


class GKCRoomView : virtual public IKCView, virtual public IKCCompositionObserver, virtual public IKCDriven
{
public:
	GKCRoomView(KCRoom* room);
	~GKCRoomView();

	//getters
	static int							getCardsCount();
	static int							getMaxCardsZOrder();
	GKCTableView*						getTableView() const;
	GKCPlayerView*						getOwnerView() const;
	std::set<GKCPlayerView*>			getPlayerViews() const;
	virtual IKCCompositionObserver*		getObserver() const;
	GKCMenuItem*						getMenuItem1()	const;
	GKCMenuItem*						getMenuItem2()	const;
	GKCMenuItem*						getMenuItem3()	const;
	GKCMenuItem*						getMenuItem4()	const;
	GKCMenuItem*						getMenuItem5()	const;

	//setters
	static void		setCardsCount(int cardsCount);
	static void		setMaxCardsZOrder(int cardsZOrder);
	void			addPlayerView(GKCPlayerView* playerView);
	void			removePlayerView(GKCPlayerView* playerView);
	virtual void	setObserver(IKCCompositionObserver* observer);
	void			setMenuItemsButtonZOrder(int zOrder);
	void			setMenuItemsTextViewZOrder(int zOrder);
	void			setMenuItemsImageViewZOrder(int zOrder);

	virtual void		propertyChanged(std::shared_ptr<KCCommand> command);
	void				menuItemInit();
	void				setupCallbacks();
	GKCPlayerView*		findPlayerView(KCPlayer* player);

private:
	GKCRoomView(const GKCRoomView& r);

	IKCCompositionObserver* m_observer;
	KCRoom* m_room;
	GKCTableView* m_tableView;
	GKCPlayerView* m_ownerView;
	std::set<GKCPlayerView*> m_playerViews;
	
	GKCMenuItem* m_menuItem1;
	GKCMenuItem* m_menuItem2;
	GKCMenuItem* m_menuItem3;
	GKCMenuItem* m_menuItem4;
	GKCMenuItem* m_menuItem5;
};