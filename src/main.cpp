/**
 * Include the Geode headers.
 */
#include <Geode/Geode.hpp>
#include <Geode/modify/EditButtonBar.hpp>
#include <Geode/modify/EditorUI.hpp>
#include <Geode/loader/Loader.hpp>

#include <alphalaneous.editortab_api/include/EditorTabs.hpp>

// define a macro for adding an object
#define ADD_OBJ(id, type) addObj(static_cast<EditorUI*>(ui), id, ObjTypes::type, items)

/**
 * Brings cocos2d and all Geode namespaces 
 * to the current scope.
 */
using namespace geode::prelude;

// enum for types of unlisted objs
enum class ObjTypes {
	NON_REPLICABLE,
	STABLE,
	UNSTABLE
};

void addObj(EditorUI* ui, int objId, enum ObjTypes necessary, cocos2d::CCArray* oArr);

// gets a reference to the editor UI
class $modify(UnlistedObjectsUI, EditorUI) {
	struct Fields {
		// a series of booleans to prevent a bug where objects are duplicated
		// when they populate in the preexisting EditButtonBars
		// They are set to false when the EditorUI is loaded, and set to true 
		// when the tab is loaded for the first time
		bool block;
		bool outline;
		bool slope;
		bool hazard;
		bool threeD;
		bool portal;
		bool monster;
		bool pixel;
		bool collectable;
		bool icon;
		bool deco;
		bool sawblade;
		bool trigger;
	};

	bool init(LevelEditorLayer* layer) {
		// set the booleans to false - see above
		m_fields->block = false;
		m_fields->outline = false;
		m_fields->slope = false;
		m_fields->hazard = false;
		m_fields->threeD = false;
		m_fields->portal = false;
		m_fields->monster = false;
		m_fields->pixel = false;
		m_fields->collectable = false;
		m_fields->icon = false;
		m_fields->deco = false;
		m_fields->sawblade = false;
		m_fields->trigger = false;

		if (!EditorUI::init(layer)) { return false; }
		// the following lines will be re-enabled when alphalaneous updates editor tab API for 2.207
		// check settings
		std::string separateTab = Mod::get()->template getSettingValue<std::string>("separateTab");
		bool unecessary = Mod::get()->template getSettingValue<bool>("doNotInclude");
		bool active = Mod::get()->template getSettingValue<bool>("activate");
		bool noUnstable = true;
		//bool noUnstable = Mod::get()->template getSettingValue<bool>("removeUnstable");

		if (separateTab=="Separate Tabs" && active) {
			// add the new blocks tab
			EditorTabs::addTab(this, TabType::BUILD, "newBlocks"_spr, [](EditorUI* ui, CCMenuItemToggler* toggler)->CCNode* {
				auto items = CCArray::create();

				// old half-slab, replaced with colorable one
				ADD_OBJ(40, NON_REPLICABLE);
				ADD_OBJ(369, STABLE);
				ADD_OBJ(370, STABLE);
				// old quarter-blocks, replaced with colorable one
				ADD_OBJ(195, NON_REPLICABLE);
				ADD_OBJ(196, NON_REPLICABLE);
				// old grey stripes going in,
				// replaced with version without outlines
				ADD_OBJ(160, STABLE);
				ADD_OBJ(161, STABLE);
				ADD_OBJ(162, STABLE);
				ADD_OBJ(163, STABLE);
				ADD_OBJ(164, STABLE);
				ADD_OBJ(165, STABLE);
				ADD_OBJ(166, STABLE);
				ADD_OBJ(167, STABLE);
				ADD_OBJ(168, STABLE);
				ADD_OBJ(169, STABLE);
				ADD_OBJ(193, STABLE);
				ADD_OBJ(737, STABLE);
				// old colored grid blocks, unknown why replaced
				ADD_OBJ(247, STABLE);
				ADD_OBJ(248, STABLE);
				ADD_OBJ(249, STABLE);
				ADD_OBJ(250, STABLE);
				ADD_OBJ(251, STABLE);
				ADD_OBJ(252, STABLE);
				ADD_OBJ(253, STABLE);
				ADD_OBJ(254, STABLE);
				// unique variation of existing blocks, placed by Build Helper
				for (int i = 2808; i <= 2837; i++) {
					ADD_OBJ(i, STABLE);
				}

				auto spr = CCSprite::create("NewBlockLabel.png"_spr);
				spr->setScale(0.4f);
				EditorTabUtils::setTabIcons(toggler, spr, spr);
				return EditorTabUtils::createEditButtonBar(items, ui);
				}, [](EditorUI*, bool state, CCNode*) {
			});
			// If you have all stable objects on, add the new Slopes tab
			if (!unecessary) {
				EditorTabs::addTab(this, TabType::BUILD, "newSlopes"_spr, [](EditorUI* ui, CCMenuItemToggler* toggler)->CCNode* {
					auto items = CCArray::create();

					// old grey grid slopes, unknown why replaced
					ADD_OBJ(289, STABLE);
					ADD_OBJ(291, STABLE);
					// other variants of slopes with outlines
					ADD_OBJ(709, STABLE);
					ADD_OBJ(710, STABLE);
					ADD_OBJ(711, STABLE);
					ADD_OBJ(712, STABLE);
					ADD_OBJ(726, STABLE);
					ADD_OBJ(727, STABLE);
					ADD_OBJ(728, STABLE);
					ADD_OBJ(729, STABLE);
					ADD_OBJ(321, STABLE);
					ADD_OBJ(323, STABLE);
					ADD_OBJ(331, STABLE);
					ADD_OBJ(333, STABLE);
					ADD_OBJ(343, STABLE);
					ADD_OBJ(345, STABLE);
					ADD_OBJ(353, STABLE);
					ADD_OBJ(355, STABLE);
					ADD_OBJ(337, STABLE);
					ADD_OBJ(339, STABLE);
					ADD_OBJ(483, STABLE);
					ADD_OBJ(484, STABLE);
					ADD_OBJ(492, STABLE);
					ADD_OBJ(493, STABLE);
					ADD_OBJ(651, STABLE);
					ADD_OBJ(652, STABLE);
					ADD_OBJ(886, STABLE);
					ADD_OBJ(887, STABLE);
					ADD_OBJ(299, STABLE);
					ADD_OBJ(301, STABLE);
					ADD_OBJ(309, STABLE);
					ADD_OBJ(311, STABLE);
					ADD_OBJ(315, STABLE);
					ADD_OBJ(317, STABLE);

					auto spr = CCSprite::create("SlopeLabel.png"_spr);
					spr->setScale(0.4f);
					EditorTabUtils::setTabIcons(toggler, spr, spr);
					return EditorTabUtils::createEditButtonBar(items, ui);
					}, [](EditorUI*, bool state, CCNode*) {
				});
			}
			// add the tab with 3D lines and better slope outlines
			EditorTabs::addTab(this,TabType::BUILD, "NewOutlines"_spr, [](EditorUI* ui, CCMenuItemToggler* toggler)->CCNode* {
				auto items = CCArray::create();

				// alternate basic slope outlines
				// fit with blocks better
				ADD_OBJ(665, NON_REPLICABLE);
				ADD_OBJ(666, NON_REPLICABLE);
				// 3D lines with hitboxes
				ADD_OBJ(1561, NON_REPLICABLE);
				ADD_OBJ(1562, NON_REPLICABLE);
				ADD_OBJ(1563, NON_REPLICABLE);
				ADD_OBJ(1564, NON_REPLICABLE);
				ADD_OBJ(1565, NON_REPLICABLE);
				ADD_OBJ(1566, NON_REPLICABLE);
				ADD_OBJ(1567, NON_REPLICABLE);
				ADD_OBJ(1568, NON_REPLICABLE);
				ADD_OBJ(1569, NON_REPLICABLE);

				auto spr = CCSprite::create("3DLabel.png"_spr);
				spr->setScale(0.8f);
				EditorTabUtils::setTabIcons(toggler, spr, spr);
				return EditorTabUtils::createEditButtonBar(items, ui);
				}, [](EditorUI*, bool state, CCNode*) {
			});
			
			// If you have all stable objects on, add a tab with more spikes and sawblades
			if (!unecessary) {
				EditorTabs::addTab(this, TabType::BUILD, "NewHazards"_spr, [](EditorUI* ui, CCMenuItemToggler* toggler)->CCNode* {
					auto items = CCArray::create();

					// old ground spike, replaced with colorable one
					ADD_OBJ(9, STABLE);
					// old curve spikes, replaced with colorable one
					ADD_OBJ(61, STABLE);
					ADD_OBJ(243, STABLE);
					ADD_OBJ(244, STABLE);
					ADD_OBJ(366, STABLE);
					ADD_OBJ(367, STABLE);
					ADD_OBJ(368, STABLE);
					// old fake spikes, unknown why replaced
					ADD_OBJ(191, STABLE);
					ADD_OBJ(198, STABLE);
					ADD_OBJ(199, STABLE);
					ADD_OBJ(393, STABLE);
					// old spiky spikes, replaced with colorable one
					ADD_OBJ(363, STABLE);
					ADD_OBJ(364, STABLE);
					ADD_OBJ(365, STABLE);
					// old bigger-curve spikes, replaced with colorable one
					ADD_OBJ(446, STABLE);
					ADD_OBJ(447, STABLE);
					// old block-on-top spikes, replaced with colorable one
					ADD_OBJ(667, STABLE);
					ADD_OBJ(989, STABLE);
					ADD_OBJ(991, STABLE);
					ADD_OBJ(720, STABLE);
					// old spike-on-top spikes, replaced with colorable ones
					ADD_OBJ(421, STABLE);
					ADD_OBJ(422, STABLE);
					ADD_OBJ(768, STABLE);
					// old sawblades, replaced with colorable ones
					ADD_OBJ(88, STABLE);
					ADD_OBJ(89, STABLE);
					ADD_OBJ(98, STABLE);
					ADD_OBJ(397, STABLE);
					ADD_OBJ(398, STABLE);
					ADD_OBJ(399, STABLE);

					auto spr = CCSprite::create("SpikeLabel.png"_spr);
					spr->setScale(0.4f);
					EditorTabUtils::setTabIcons(toggler, spr, spr);
					return EditorTabUtils::createEditButtonBar(items, ui);
					}, [](EditorUI*, bool state, CCNode*) {
				});
			}
			// if unstable objects are available, add the tab with way too many pixel objects
			if (!noUnstable) {
				EditorTabs::addTab(this, TabType::BUILD, "NewPixels"_spr, [](EditorUI* ui, CCMenuItemToggler* toggler)->CCNode* {
					auto items = CCArray::create();

					/*
						1964-2011 are random pixels
						there are so many of these
						the exact same as one of the ones
						in the pixel blocks tab
						this is much easier to write for adding them to the editor 
					*/
					for (int i = 1964; i <= 2011; i++) {
						ADD_OBJ(i, UNSTABLE);
					}

					auto spr = CCSprite::create("PixelLabel.png"_spr);
					spr->setScale(0.6f);
					EditorTabUtils::setTabIcons(toggler, spr, spr);
					return EditorTabUtils::createEditButtonBar(items, ui);
					}, [](EditorUI*, bool state, CCNode*) {
				});
			}
			// If you have all stable objects on, add the tab with new deco objects
			if (!unecessary) {
				EditorTabs::addTab(this, TabType::BUILD, "newDeco"_spr, [](EditorUI* ui, CCMenuItemToggler* toggler)->CCNode* {
					auto items = CCArray::create();

					// old version of circle, unknown why replaced
					ADD_OBJ(725, STABLE);
					// old bush versions, unknown why replaced
					ADD_OBJ(461, STABLE);
					ADD_OBJ(462, STABLE);
					ADD_OBJ(463, STABLE);
					ADD_OBJ(464, STABLE);
					ADD_OBJ(465, STABLE);
					ADD_OBJ(466, STABLE);

					auto spr = CCSprite::create("BushLabel.png"_spr);
					spr->setScale(0.3f);
					EditorTabUtils::setTabIcons(toggler, spr, spr);
					return EditorTabUtils::createEditButtonBar(items, ui);
					}, [](EditorUI*, bool state, CCNode*) {
				});
			}
			// add the tab with unusual objects
			EditorTabs::addTab(this, TabType::BUILD, "UnusualObjs"_spr, [](EditorUI* ui, CCMenuItemToggler* toggler)->CCNode* {
				auto items = CCArray::create();

				// solid startPos
				ADD_OBJ(34, NON_REPLICABLE);
				// other weird block (looks like it uses a weird mishmash of textures)
				ADD_OBJ(3800, NON_REPLICABLE);

				auto spr = CCSprite::create("StartPosLabel.png"_spr);
				spr->setScale(0.6f);
				EditorTabUtils::setTabIcons(toggler, spr, spr);
				return EditorTabUtils::createEditButtonBar(items, ui);
				}, [](EditorUI*, bool state, CCNode*) {
			});
			// If you have all stable objects on, add the tab with more triggers
			if (!unecessary) {
				EditorTabs::addTab(this, TabType::BUILD, "newTriggers"_spr, [](EditorUI* ui, CCMenuItemToggler* toggler)->CCNode* {
					auto items = CCArray::create();
					// old color Triggers
					// replaced with general all-colors trigger in 2.0
					ADD_OBJ(29, UNSTABLE);
					ADD_OBJ(30, UNSTABLE);
					ADD_OBJ(104, UNSTABLE);
					ADD_OBJ(105, UNSTABLE);
					ADD_OBJ(744, UNSTABLE);
					ADD_OBJ(915, UNSTABLE);
					// early version of the end trigger. It does not work at all anymore. 
					ADD_OBJ(1931, STABLE);
					// State block with no number?
					ADD_OBJ(3655, STABLE);

					auto spr = CCSprite::create("TriggerLabel.png"_spr);
					spr->setScale(0.4f);
					EditorTabUtils::setTabIcons(toggler, spr, spr);
					return EditorTabUtils::createEditButtonBar(items, ui);
					}, [](EditorUI*, bool state, CCNode*) {
				}); 
			}
		}
		if (separateTab == "Single Tab" && active) {
			EditorTabs::addTab(this, TabType::BUILD, "allUnlistedObjs"_spr, [](EditorUI* ui, CCMenuItemToggler* toggler)->CCNode* {
				auto items = CCArray::create();
				// old half-slab, replaced with colorable one
				ADD_OBJ(40, NON_REPLICABLE);
				ADD_OBJ(369, STABLE);
				ADD_OBJ(370, STABLE);
				// old quarter-blocks, replaced with colorable one
				ADD_OBJ(195, NON_REPLICABLE);
				ADD_OBJ(196, NON_REPLICABLE);
				// old grey stripes going in,
				// replaced with version without outlines
				ADD_OBJ(160, STABLE);
				ADD_OBJ(161, STABLE);
				ADD_OBJ(162, STABLE);
				ADD_OBJ(163, STABLE);
				ADD_OBJ(164, STABLE);
				ADD_OBJ(165, STABLE);
				ADD_OBJ(166, STABLE);
				ADD_OBJ(167, STABLE);
				ADD_OBJ(168, STABLE);
				ADD_OBJ(169, STABLE);
				ADD_OBJ(193, STABLE);
				ADD_OBJ(737, STABLE);
				// old colored grid blocks, unknown why replaced
				ADD_OBJ(247, STABLE);
				ADD_OBJ(248, STABLE);
				ADD_OBJ(249, STABLE);
				ADD_OBJ(250, STABLE);
				ADD_OBJ(251, STABLE);
				ADD_OBJ(252, STABLE);
				ADD_OBJ(253, STABLE);
				ADD_OBJ(254, STABLE);
				// unique variation of existing blocks, placed by Build Helper
				for (int i = 2808; i <= 2837; i++) {
					ADD_OBJ(i, STABLE);
				}
				// old grey grid slopes, unknown why replaced
				ADD_OBJ(289, STABLE);
				ADD_OBJ(291, STABLE);
				// other variants of slopes with outlines
				ADD_OBJ(709, STABLE);
				ADD_OBJ(710, STABLE);
				ADD_OBJ(711, STABLE);
				ADD_OBJ(712, STABLE);
				ADD_OBJ(726, STABLE);
				ADD_OBJ(727, STABLE);
				ADD_OBJ(728, STABLE);
				ADD_OBJ(729, STABLE);
				ADD_OBJ(321, STABLE);
				ADD_OBJ(323, STABLE);
				ADD_OBJ(331, STABLE);
				ADD_OBJ(333, STABLE);
				ADD_OBJ(343, STABLE);
				ADD_OBJ(345, STABLE);
				ADD_OBJ(353, STABLE);
				ADD_OBJ(355, STABLE);
				ADD_OBJ(337, STABLE);
				ADD_OBJ(339, STABLE);
				ADD_OBJ(483, STABLE);
				ADD_OBJ(484, STABLE);
				ADD_OBJ(492, STABLE);
				ADD_OBJ(493, STABLE);
				ADD_OBJ(651, STABLE);
				ADD_OBJ(652, STABLE);
				ADD_OBJ(886, STABLE);
				ADD_OBJ(887, STABLE);
				ADD_OBJ(299, STABLE);
				ADD_OBJ(301, STABLE);
				ADD_OBJ(309, STABLE);
				ADD_OBJ(311, STABLE);
				ADD_OBJ(315, STABLE);
				ADD_OBJ(317, STABLE);
				// alternate basic slope outlines
				// fit with blocks better
				ADD_OBJ(665, NON_REPLICABLE);
				ADD_OBJ(666, NON_REPLICABLE);
				// 3D lines with hitboxes
				ADD_OBJ(1561, NON_REPLICABLE);
				ADD_OBJ(1562, NON_REPLICABLE);
				ADD_OBJ(1563, NON_REPLICABLE);
				ADD_OBJ(1564, NON_REPLICABLE);
				ADD_OBJ(1565, NON_REPLICABLE);
				ADD_OBJ(1566, NON_REPLICABLE);
				ADD_OBJ(1567, NON_REPLICABLE);
				ADD_OBJ(1568, NON_REPLICABLE);
				ADD_OBJ(1569, NON_REPLICABLE);
				// old ground spike, replaced with colorable one
				ADD_OBJ(9, STABLE);
				// old curve spikes, replaced with colorable one
				ADD_OBJ(61, STABLE);
				ADD_OBJ(243, STABLE);
				ADD_OBJ(244, STABLE);
				ADD_OBJ(366, STABLE);
				ADD_OBJ(367, STABLE);
				ADD_OBJ(368, STABLE);
				// old fake spikes, unknown why replaced
				ADD_OBJ(191, STABLE);
				ADD_OBJ(198, STABLE);
				ADD_OBJ(199, STABLE);
				ADD_OBJ(393, STABLE);
				// old spiky spikes, replaced with colorable one
				ADD_OBJ(363, STABLE);
				ADD_OBJ(364, STABLE);
				ADD_OBJ(365, STABLE);
				// old bigger-curve spikes, replaced with colorable one
				ADD_OBJ(446, STABLE);
				ADD_OBJ(447, STABLE);
				// old block-on-top spikes, replaced with colorable one
				ADD_OBJ(667, STABLE);
				ADD_OBJ(989, STABLE);
				ADD_OBJ(991, STABLE);
				ADD_OBJ(720, STABLE);
				// old spike-on-top spikes, replaced with colorable ones
				ADD_OBJ(421, STABLE);
				ADD_OBJ(422, STABLE);
				ADD_OBJ(768, STABLE);
				// old sawblades, replaced with colorable ones
				ADD_OBJ(88, STABLE);
				ADD_OBJ(89, STABLE);
				ADD_OBJ(98, STABLE);
				ADD_OBJ(397, STABLE);
				ADD_OBJ(398, STABLE);
				ADD_OBJ(399, STABLE);
				/*
					1964-2011 are random pixels
					there are so many of these
					the exact same as one of the ones
					in the pixel blocks tab
					this is much easier to write for adding them to the editor
				*/
				for (int i = 1964; i <= 2011; i++) {
					ADD_OBJ(i, UNSTABLE);
				}
				// old version of circle, unknown why replaced
				ADD_OBJ(725, STABLE);
				// old bush versions, unknown why replaced
				ADD_OBJ(461, STABLE);
				ADD_OBJ(462, STABLE);
				ADD_OBJ(463, STABLE);
				ADD_OBJ(464, STABLE);
				ADD_OBJ(465, STABLE);
				ADD_OBJ(466, STABLE);
				// old color Triggers (do not work as fas as I know)
				// replaced with general all-colors trigger in 2.0
				ADD_OBJ(29, UNSTABLE);
				ADD_OBJ(30, UNSTABLE);
				ADD_OBJ(104, UNSTABLE);
				ADD_OBJ(105, UNSTABLE);
				ADD_OBJ(744, UNSTABLE);
				ADD_OBJ(915, UNSTABLE);
				// early version of the end trigger. It does not work at all anymore. 
				ADD_OBJ(1931, STABLE);
				// State block with no number?
				ADD_OBJ(3655, STABLE);
				// solid startPos
				ADD_OBJ(34, NON_REPLICABLE);
				// other weird block (looks like it uses a weird mishmash of textures)
				ADD_OBJ(3800, NON_REPLICABLE);

				auto spr = CCSprite::create("StartPosLabel.png"_spr);
				spr->setScale(0.6f);
				EditorTabUtils::setTabIcons(toggler, spr, spr);
				return EditorTabUtils::createEditButtonBar(items, ui);
				}, [](EditorUI*, bool state, CCNode*) {
			});
		}
		return true;
	}
};

// adds an object to an editor tab
void addObj(EditorUI* ui, int objId, enum ObjTypes necessary, cocos2d::CCArray* oArr) {
	
	bool unecessary = Mod::get()->template getSettingValue<bool>("doNotInclude");
	bool active = Mod::get()->template getSettingValue<bool>("activate");
	bool noUnstable = true;
	//bool noUnstable = Mod::get()->template getSettingValue<bool>("removeUnstable");

	// if all objects are to be shown, 
	// or if it is unecessary and !unecessary, 
	// or if it is nonReplicable

	if(!noUnstable||
		(necessary==ObjTypes::STABLE&&!unecessary)||
		necessary==ObjTypes::NON_REPLICABLE) {
		//first argument is obj id, 2nd is always 4
		auto obj=ui->getCreateBtn(objId,4);
		if (obj && oArr->indexOfObject(obj) == UINT_MAX) {
			oArr->addObject(obj);
		}
	}
}

// modify the EditButtonBar
class $modify(EditButtonBar) {
	
	$override
	void loadFromItems(CCArray * items, int r, int c, bool unkBool) {

		std::string separateTab = Mod::get()->template getSettingValue<std::string>("separateTab");
		bool active = Mod::get()->template getSettingValue<bool>("activate");

		UnlistedObjectsUI* ui = static_cast<UnlistedObjectsUI*>(this->getParent());

		if (!active||separateTab!="Normal Tabs") {
			EditButtonBar::loadFromItems(items, r, c, unkBool);
			return;
		}
		if (this->getID() == "block-tab-bar" && !ui->m_fields->block) {
			// old half-slab, replaced with colorable one
			ADD_OBJ(40, NON_REPLICABLE);
			ADD_OBJ(369, STABLE);
			ADD_OBJ(370, STABLE);
			// old quarter-blocks, replaced with colorable one
			ADD_OBJ(195, NON_REPLICABLE);
			ADD_OBJ(196, NON_REPLICABLE);
			// old grey stripes going in,
			// replaced with version without outlines
			ADD_OBJ(160, STABLE);
			ADD_OBJ(161, STABLE);
			ADD_OBJ(162, STABLE);
			ADD_OBJ(163, STABLE);
			ADD_OBJ(164, STABLE);
			ADD_OBJ(165, STABLE);
			ADD_OBJ(166, STABLE);
			ADD_OBJ(167, STABLE);
			ADD_OBJ(168, STABLE);
			ADD_OBJ(169, STABLE);
			ADD_OBJ(193, STABLE);
			ADD_OBJ(737, STABLE);
			// old colored grid blocks, unknown why replaced
			ADD_OBJ(247, STABLE);
			ADD_OBJ(248, STABLE);
			ADD_OBJ(249, STABLE);
			ADD_OBJ(250, STABLE);
			ADD_OBJ(251, STABLE);
			ADD_OBJ(252, STABLE);
			ADD_OBJ(253, STABLE);
			ADD_OBJ(254, STABLE);
			// unique variation of existing blocks, placed by Build Helper
			for (int i = 2808; i <= 2837; i++) {
				ADD_OBJ(i, STABLE);
			}
			// solid startPos
			ADD_OBJ(34, NON_REPLICABLE);
			// other weird block (looks like it uses a weird mishmash of textures)
			ADD_OBJ(3800, NON_REPLICABLE);
			ui->m_fields->block = true;
		}
		else if (this->getID() == "outline-tab-bar" && !ui->m_fields->outline) {
			// alternate basic slope outlines
			// fit with blocks better
			ADD_OBJ(665, NON_REPLICABLE);
			ADD_OBJ(666, NON_REPLICABLE);
			ui->m_fields->outline = true;
		}
		else if (this->getID() == "slope-tab-bar" && !ui->m_fields->slope) {
			// old grey grid slopes, unknown why replaced
			ADD_OBJ(289, STABLE);
			ADD_OBJ(291, STABLE);
			// other variants of slopes with outlines
			ADD_OBJ(709, STABLE);
			ADD_OBJ(710, STABLE);
			ADD_OBJ(711, STABLE);
			ADD_OBJ(712, STABLE);
			ADD_OBJ(726, STABLE);
			ADD_OBJ(727, STABLE);
			ADD_OBJ(728, STABLE);
			ADD_OBJ(729, STABLE);
			ADD_OBJ(321, STABLE);
			ADD_OBJ(323, STABLE);
			ADD_OBJ(331, STABLE);
			ADD_OBJ(333, STABLE);
			ADD_OBJ(343, STABLE);
			ADD_OBJ(345, STABLE);
			ADD_OBJ(353, STABLE);
			ADD_OBJ(355, STABLE);
			ADD_OBJ(337, STABLE);
			ADD_OBJ(339, STABLE);
			ADD_OBJ(483, STABLE);
			ADD_OBJ(484, STABLE);
			ADD_OBJ(492, STABLE);
			ADD_OBJ(493, STABLE);
			ADD_OBJ(651, STABLE);
			ADD_OBJ(652, STABLE);
			ADD_OBJ(886, STABLE);
			ADD_OBJ(887, STABLE);
			ADD_OBJ(299, STABLE);
			ADD_OBJ(301, STABLE);
			ADD_OBJ(309, STABLE);
			ADD_OBJ(311, STABLE);
			ADD_OBJ(315, STABLE);
			ADD_OBJ(317, STABLE);
			ui->m_fields->slope = true;
		}
		else if (this->getID() == "hazard-tab-bar" && !ui->m_fields->hazard) {
			// old ground spike, replaced with colorable one
			ADD_OBJ(9, STABLE);
			// old curve spikes, replaced with colorable one
			ADD_OBJ(61, STABLE);
			ADD_OBJ(243, STABLE);
			ADD_OBJ(244, STABLE);
			ADD_OBJ(366, STABLE);
			ADD_OBJ(367, STABLE);
			ADD_OBJ(368, STABLE);
			// old fake spikes, unknown why replaced
			ADD_OBJ(191, STABLE);
			ADD_OBJ(198, STABLE);
			ADD_OBJ(199, STABLE);
			ADD_OBJ(393, STABLE);
			// old spiky spikes, replaced with colorable one
			ADD_OBJ(363, STABLE);
			ADD_OBJ(364, STABLE);
			ADD_OBJ(365, STABLE);
			// old bigger-curve spikes, replaced with colorable one
			ADD_OBJ(446, STABLE);
			ADD_OBJ(447, STABLE);
			// old block-on-top spikes, replaced with colorable one
			ADD_OBJ(667, STABLE);
			ADD_OBJ(989, STABLE);
			ADD_OBJ(991, STABLE);
			ADD_OBJ(720, STABLE);
			// old spike-on-top spikes, replaced with colorable ones
			ADD_OBJ(421, STABLE);
			ADD_OBJ(422, STABLE);
			ADD_OBJ(768, STABLE);
			ui->m_fields->hazard = true;
		}
		else if (this->getID() == "3d-tab-bar" && !ui->m_fields->threeD) {
			// 3D lines with hitboxes
			ADD_OBJ(1561, NON_REPLICABLE);
			ADD_OBJ(1562, NON_REPLICABLE);
			ADD_OBJ(1563, NON_REPLICABLE);
			ADD_OBJ(1564, NON_REPLICABLE);
			ADD_OBJ(1565, NON_REPLICABLE);
			ADD_OBJ(1566, NON_REPLICABLE);
			ADD_OBJ(1567, NON_REPLICABLE);
			ADD_OBJ(1568, NON_REPLICABLE);
			ADD_OBJ(1569, NON_REPLICABLE);
			ui->m_fields->threeD = true;
		}
		else if (this->getID() == "portal-tab-bar" && !ui->m_fields->portal) {
			ui->m_fields->portal = true;
		}
		else if (this->getID() == "monster-tab-bar"&&!ui->m_fields->monster) {
			ui->m_fields->monster = true;
		}
		else if (this->getID() == "pixel-tab-bar"&&!ui->m_fields->pixel) {
			/*
				1964-2011 are random pixels
				there are so many of these
				the exact same as one of the ones
				in the pixel blocks tab
				this is much easier to write for adding them to the editor
			*/

			for(int i=1964;i<=2011;i++) {
				ADD_OBJ(i,UNSTABLE);
			}
			ui->m_fields->pixel = true;
		}
		else if (this->getID() == "collectable-tab-bar"&&!ui->m_fields->collectable) {
			ui->m_fields->collectable = true;
		}
		else if (this->getID() == "icon-tab-bar"&&!ui->m_fields->icon) {
			ui->m_fields->icon = true;
		}
		else if (this->getID() == "deco-tab-bar"&&!ui->m_fields->deco) {
			// old version of circle, unknown why replaced
			ADD_OBJ(725, STABLE);
			// old bush versions, unknown why replaced
			ADD_OBJ(461, STABLE);
			ADD_OBJ(462, STABLE);
			ADD_OBJ(463, STABLE);
			ADD_OBJ(464, STABLE);
			ADD_OBJ(465, STABLE);
			ADD_OBJ(466, STABLE);
			ui->m_fields->deco = true;
		}
		else if (this->getID() == "sawblade-tab-bar"&&!ui->m_fields->sawblade) {
			// old sawblades, replaced with colorable ones
			ADD_OBJ(88, STABLE);
			ADD_OBJ(89, STABLE);
			ADD_OBJ(98, STABLE);
			ADD_OBJ(397, STABLE);
			ADD_OBJ(398, STABLE);
			ADD_OBJ(399, STABLE);
			ui->m_fields->sawblade = true;
		}
		else if (this->getID() == "trigger-tab-bar"&&!ui->m_fields->trigger) {
			// old color Triggers (do not work as fas as I know)
			// replaced with general all-colors trigger in 2.0
			ADD_OBJ(29, UNSTABLE);
			ADD_OBJ(30, UNSTABLE);
			ADD_OBJ(104, UNSTABLE);
			ADD_OBJ(105, UNSTABLE);
			ADD_OBJ(744, UNSTABLE);
			ADD_OBJ(915, UNSTABLE);
			// early version of the end trigger. It does not work at all anymore. 
			ADD_OBJ(1931, STABLE);
			// State block with no number?
			ADD_OBJ(3655, STABLE);
			ui->m_fields->trigger = true;
		}
		EditButtonBar::loadFromItems(items, r, c, unkBool);
	}
};

