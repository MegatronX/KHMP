#include "ResourceLoadImport.h"
//#include <graphics/AnimatedSprite.h>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <graphics/Animation/FrameAnimation.h>
#include <graphics/Animation/Animator.h>
namespace Content
{
	void ResourceLoadImport::ProcessImports(const std::string& file, ContentManager* manager)
	{
		using namespace pugi;
		xml_document ResourceMap;
		xml_parse_result result = ResourceMap.load_file(file.c_str());

		if (!result)
			std::cerr << "Map Failed To Load. Error: " << result.description();
		else
		{
			for (xml_node resources = ResourceMap.child("Resources"); resources; resources = resources.next_sibling("Resources"))
			{
				for (xml_node spritesbase = resources.child("Sprites"); spritesbase; spritesbase = spritesbase.next_sibling("Sprites"))
				{
					Cache::GameStyle style = Cache::GameStyle::Main;
					std::string gamestyle = spritesbase.attribute("gamestyle").value();
					auto gs = Cache::NameToStyleMap.find(gamestyle);
					if (gs != Cache::NameToStyleMap.end())
						style = gs->second;
					for (xml_node sprite = spritesbase.child("Sprite"); sprite; sprite = sprite.next_sibling("Sprite"))
					{
						float fps = sprite.attribute("defaultfps").as_float();
						int FrameCount = 0;
						int RunningHeight = 0;
						std::string imgIndex = sprite.attribute("indexname").value();

						bool flipx = sprite.attribute("flipx").as_bool();

						std::string orientation = sprite.attribute("orientation").value();
						boost::trim(orientation);
						float scale = sprite.attribute("defaultscale").as_float();
						/*if (scale > 0)
							sprLoad.StartingScale = sf::Vector2f(scale, scale);
						else
						{
							float xscale = sprite.attribute("defaultscalex").as_float();
							float yscale = sprite.attribute("defaultscaley").as_float();
							if (xscale > 0)
								sprLoad.StartingScale.x = xscale;
							if (yscale > 0)
								sprLoad.StartingScale.y = yscale;
						}*/
						std::string defaultrow = sprite.attribute("defaultrow").value();
						//Graphics::RowClass defRow = Graphics::RowClass::Unavailable;
						boost::trim(defaultrow);
						//auto rclassIt = Graphics::NameRowMap.find(defaultrow);

						//defRow = Graphics::NameRowMap[defaultrow];
						//if (rclassIt != Graphics::NameRowMap.end())
							//defRow = rclassIt->second;
						//sprLoad.DefRow = defRow;

						sf::Vector2f PosOffset;
						std::string posstring = sprite.attribute("defaultpositionoffset").value();
						std::vector<std::string> posfrags;
						boost::split(posfrags, posstring, boost::is_any_of(","));
						for (int i = 0; i < posfrags.size(); ++i)
							boost::trim(posfrags[i]);
						if (posfrags.size() == 2)
						{
							try
							{
								int myX = boost::lexical_cast<int>(posfrags[0]);
								PosOffset.x = myX;
								int myY = boost::lexical_cast<int>(posfrags[1]);
								PosOffset.y = myY;
							}
							catch (std::exception ex)
							{
								std::cerr << "Error loading resource. " << ex.what() << std::endl; 
							}
						}
						//sprLoad.PosOffset = PosOffset;

						bool SpriteWideFPSSet = false;
						float overallFPS = 0;
						auto fpsattribute = sprite.attribute("defaultfps");
						if (!fpsattribute.empty())
						{
							SpriteWideFPSSet = true;
							overallFPS = fpsattribute.as_float();
						}
						//flipx="false" defaultscale="1.0" defaultpositionoffset="-50, 50"

						int runningOffset = 0;
						auto anim = boost::shared_ptr<::Graphics::Animator>(new ::Graphics::Animator());
						for (xml_node row = sprite.child("Row"); row; row = row.next_sibling("Row"))
						{
							auto frameAnim = ::Graphics::FrameAnimation::create();
							int framewidth, frameheight, framecount;
							int xoffset = 0;
							int yoffset = runningOffset;
							std::string rclassstring = row.attribute("rowtypes").value();
							std::vector<std::string> frags;
							boost::split(frags, rclassstring, boost::is_any_of(","));

							std::vector<std::string> rowaliases;
							rowaliases.reserve(frags.size());
							for (int index = 0; index < frags.size(); ++index)
							{
								boost::trim(frags[index]);
								rowaliases.push_back(frags[index]);
								
							}

							framewidth = row.attribute("framewidth").as_int();
							frameheight = row.attribute("frameheight").as_int();
							framecount = row.attribute("framecount").as_int();

							std::string fpsSet = row.attribute("fps").value();
							std::vector<std::string> fpsFrags;
							std::vector<float> RowFPSSet;
							if (fpsSet.length() > 0)
							{

								boost::split(fpsFrags, fpsSet, boost::is_any_of(","));
								for (int i = 0; i < fpsFrags.size(); ++i)
								{
									boost::trim(fpsFrags[i]);
									try
									{
										RowFPSSet.push_back(boost::lexical_cast<float>(fpsFrags[i]));
									}
									catch (std::exception)
									{
										std::cerr << "Bad FPS conversion " << fpsFrags[i] << std::endl;
									}
								}
							}

							for (int i = 0; i < framecount; ++i)
							{
								frameAnim->AddFrame(1.f, sf::IntRect(xoffset + i * framewidth, yoffset, framewidth, frameheight));
							}

							for (int i = 0; i < rowaliases.size(); ++i)
							{
								float fps = 1;
								if (i >= RowFPSSet.size())
								{
									if (RowFPSSet.size() > 0)
										fps = *RowFPSSet.end();
								}
								else
								{
									fps = RowFPSSet[i];
								}

								anim->AddAnimation(rowaliases[i], frameAnim, sf::milliseconds((1000.f / fps) * static_cast<float>(framecount)));
								if (rowaliases[i] == defaultrow)
								{
									anim->SetDefaultAnimation(frameAnim, sf::milliseconds((1000.f / fps) * static_cast<float>(framecount)));
								}
							}
							
							for (xml_node subrow = row.child("SubRow"); subrow; subrow = subrow.next_sibling("Row"))
							{
								auto subframeAnim = ::Graphics::FrameAnimation::create();
								int framestart = subrow.attribute("rowframestart").as_int();
								int frameend = subrow.attribute("rowframeend").as_int();
								std::string rsubclassstring = subrow.attribute("rowtypes").value();
								std::vector<std::string> frags2;
								boost::split(frags2, rsubclassstring, boost::is_any_of(","));
								auto subrowfps = subrow.attribute("fps");
								float subfps = 3;
								if (SpriteWideFPSSet)
									subfps = overallFPS;
								if (!subrowfps.empty())
									subfps = subrowfps.as_float();

								std::vector<std::string> rowaliases2;
								rowaliases2.reserve(frags2.size());
								for (int index = 0; index < frags2.size(); ++index)
								{
									boost::trim(frags2[index]);
									rowaliases2.push_back(frags2[index]);
								}
								for (int i = framestart; i <= frameend; ++i)
								{
									subframeAnim->AddFrame(1.f, sf::IntRect(xoffset + i * framewidth, yoffset, framewidth, frameheight));
								}
								for (int i = 0; i < rowaliases2.size(); ++i)
								{
									float fps = 1;
									if (i >= RowFPSSet.size())
									{
										if (RowFPSSet.size() > 0)
											fps = *RowFPSSet.end();
									}
									anim->AddAnimation(rowaliases2[i], subframeAnim, sf::milliseconds((1000.f / subfps) * static_cast<float>(frameend - framestart)));
								}

								rowaliases2.clear();
							}
							

							runningOffset += frameheight;
						}
						manager->StoredAnimators[imgIndex + "_" + gamestyle] = anim;
					}
				}
			}
		}

		/*using namespace pugi;
		xml_document mapDoc;
		//using namespace Rows;
		using namespace Graphics;
		
		xml_parse_result result = mapDoc.load_file(file.c_str());
		if (!result)
			std::cerr << "Map Failed To Load. Error: " << result.description();
		else
		{
			for (xml_node resources = mapDoc.child("Resources"); resources; resources = resources.next_sibling("Resources"))
			{
				for (xml_node spritesbase = resources.child("Sprites"); spritesbase; spritesbase = spritesbase.next_sibling("Sprites"))
				{
					Cache::GameStyle style = Cache::GameStyle::Main;
					std::string gamestyle = spritesbase.attribute("gamestyle").value();
					auto gs = Cache::NameToStyleMap.find(gamestyle);
					if (gs != Cache::NameToStyleMap.end())
						style = gs->second;
					for (xml_node sprite = spritesbase.child("Sprite"); sprite; sprite = sprite.next_sibling("Sprite"))
					{
						SpriteLoadDescription sprLoad;
						sprLoad.StartingFPS = sprite.attribute("defaultfps").as_float();
						int FrameCount = 0;
						int RunningHeight = 0;
						std::string imgIndex = sprite.attribute("indexname").value();

						bool flipx = sprite.attribute("flipx").as_bool();
						sprLoad.FlipX = flipx;
						
						std::string orientation = sprite.attribute("orientation").value();
						boost::trim(orientation);
						if (orientation == "Left" || orientation == "left")
						{
							sprLoad.Orientation = Graphics::SpriteOrientation::SprLeft;
						}
						else if (orientation == "Right" || orientation == "right")
						{
							sprLoad.Orientation = Graphics::SpriteOrientation::SprRight;
						}
						float scale = sprite.attribute("defaultscale").as_float();
						if (scale > 0)
							sprLoad.StartingScale = sf::Vector2f(scale, scale);
						else
						{
							float xscale = sprite.attribute("defaultscalex").as_float();
							float yscale = sprite.attribute("defaultscaley").as_float();
							if (xscale > 0)
								sprLoad.StartingScale.x = xscale;
							if (yscale > 0)
								sprLoad.StartingScale.y = yscale;
						}
						std::string defaultrow = sprite.attribute("defaultrow").value();
						Graphics::RowClass defRow = Graphics::RowClass::Unavailable;
						boost::trim(defaultrow);
						auto rclassIt = Graphics::NameRowMap.find(defaultrow);

						//defRow = Graphics::NameRowMap[defaultrow];
						if (rclassIt != Graphics::NameRowMap.end())
							defRow = rclassIt->second;
						sprLoad.DefRow = defRow;

						sf::Vector2f PosOffset;
						std::string posstring = sprite.attribute("defaultpositionoffset").value();
						std::vector<std::string> posfrags;
						boost::split(posfrags, posstring, boost::is_any_of(","));
						for (int i = 0; i < posfrags.size(); ++i)
							boost::trim(posfrags[i]);
						if (posfrags.size() == 2)
						{
							try
							{
								int myX = boost::lexical_cast<int>(posfrags[0]);
								PosOffset.x = myX;
								int myY = boost::lexical_cast<int>(posfrags[1]);
								PosOffset.y = myY;
							}
							catch (std::exception ex)
							{
								std::cerr << "Error loading resource. " << ex.what() << std::endl; 
							}
						}
						sprLoad.PosOffset = PosOffset;

						bool SpriteWideFPSSet = false;
						float overallFPS = 0;
						auto fpsattribute = sprite.attribute("defaultfps");
						if (!fpsattribute.empty())
						{
							SpriteWideFPSSet = true;
							overallFPS = fpsattribute.as_float();
						}
						//flipx="false" defaultscale="1.0" defaultpositionoffset="-50, 50"
						for (xml_node row = sprite.child("Row"); row; row = row.next_sibling("Row"))
						{
							std::vector<Graphics::RowClass> rowClasses;
							int framewidth, frameheight, framecount;
							std::string rclassstring = row.attribute("rowtypes").value();
							std::vector<std::string> frags;
							boost::split(frags, rclassstring, boost::is_any_of(","));
							framewidth = row.attribute("framewidth").as_int();
							frameheight = row.attribute("frameheight").as_int();
							framecount = row.attribute("framecount").as_int();

							

							for (int index = 0; index < frags.size(); ++index)
							{
								boost::trim(frags[index]);
							}
							for (auto frag = frags.begin(); frag != frags.end(); ++frag)
							{
								auto res = Graphics::NameRowMap.find(*frag);
								if (res != Graphics::NameRowMap.end())
								{
									rowClasses.push_back(res->second);
								}
								else
								{
									std::cout << "Found non existant class row " << *frag << std::endl;
									rowClasses.push_back(Graphics::RowClass::Unavailable);
								}
							}

							std::string rowPosOffset = row.attribute("rowoffseter").value();
							std::vector<std::string> offsetFrags;
							boost::split(offsetFrags, rowPosOffset, boost::is_any_of(","));
							for (int i = 0; i < offsetFrags.size(); ++i)
								boost::trim(offsetFrags[i]);

							std::string fpsSet = row.attribute("fps").value();
							std::vector<std::string> fpsFrags;
							std::vector<float> RowFPSSet;
							if (fpsSet.length() > 0)
							{
								
								boost::split(fpsFrags, fpsSet, boost::is_any_of(","));
								for (int i = 0; i < fpsFrags.size(); ++i)
								{
									boost::trim(fpsFrags[i]);
									try
									{
										RowFPSSet.push_back(boost::lexical_cast<float>(fpsFrags[i]));
									}
									catch (std::exception)
									{
										std::cerr << "Bad FPS conversion " << fpsFrags[i] << std::endl;
									}
								}
							}
							

							int fpsindex = 0;
							for (auto rclass = rowClasses.begin(); rclass != rowClasses.end(); ++rclass, ++fpsindex)
							{
								bool fpsrowset = false;
								float rowfps = 0;
								if (SpriteWideFPSSet)
								{
									rowfps = overallFPS;
								}
								if (RowFPSSet.size() > 0)
								{
									if (fpsindex >= RowFPSSet.size())
										rowfps = RowFPSSet[RowFPSSet.size() - 1];
									else
										rowfps = RowFPSSet[fpsindex];
									fpsrowset = true;
								}
								sf::Vector2f OffsetVector;
								try
								{
									if (offsetFrags.size() == 2)
									{
										OffsetVector.x = boost::lexical_cast<int>(offsetFrags[0]);
										OffsetVector.y = boost::lexical_cast<int>(offsetFrags[1]);
									}
								}
								catch (std::exception ex)
								{
									std::cerr << "Error loading resource. " << ex.what() << std::endl; 
								}
								sprLoad.RowDescriptions.push_back(Graphics::SpriteRow(FrameCount, FrameCount + framecount - 1, *rclass, std::vector<int>(framecount, framewidth), OffsetVector, RunningHeight, 0, frameheight, rowfps));
							}
							rowClasses.clear();
							for (xml_node subrow = row.child("SubRow"); subrow; subrow = subrow.next_sibling("SubRow"))
							{
							std::vector<Graphics::RowClass> rclasses2;
							int framestart = subrow.attribute("rowframestart").as_int();
							int frameend = subrow.attribute("rowframeend").as_int();
							std::string rsubclassstring = subrow.attribute("rowtypes").value();
							std::vector<std::string> frags2;
							boost::split(frags2, rsubclassstring, boost::is_any_of(","));
							auto subrowfps = subrow.attribute("fps");
							float subfps = 3;
							if (SpriteWideFPSSet)
							subfps = overallFPS;
							if (!subrowfps.empty())
							subfps = subrowfps.as_float();
							for (int index = 0; index < frags2.size(); ++index)
							{
							boost::trim(frags2[index]);
							}
							for (auto frag = frags2.begin(); frag != frags2.end(); ++frag)
							{
							auto res = Graphics::NameRowMap.find(*frag);
							if (res != Graphics::NameRowMap.end())
							{
							rclasses2.push_back(res->second);
							}
							else
							{
							std::cout << "Found non existant class row " << *frag << std::endl;
							rclasses2.push_back(Graphics::RowClass::Unavailable);
							}
							}
							for (auto rclass = rclasses2.begin(); rclass != rclasses2.end(); ++ rclass)
							{
							sprLoad.RowDescriptions.push_back(Graphics::SpriteRow(FrameCount + framestart, FrameCount + frameend, *rclass, std::vector<int>(frameend - framestart + 1, framewidth), RunningHeight, 0, frameheight, subfps));
							}
							rclasses2.clear();
							}
							FrameCount += framecount;
							RunningHeight += frameheight;
						}
						sprLoad.FrameCount = FrameCount;
						manager->StoredSpriteRows[style][imgIndex] = sprLoad;
					}
					for (xml_node sprite = spritesbase.child("AttackSprite"); sprite; sprite = sprite.next_sibling("AttackSprite"))
					{
						AttackSpriteLoadDescription loader;
						xml_node property = sprite.child("Position");
						if (!property.empty())
						{
							
						}
						else
						{

						}

						property = sprite.child("AlphaFadeIn");
						if (property)
						{

						}

						property = sprite.child("AlphaFadeOut");
						if (property)
						{

						}

						property = sprite.child("FPSGradient");
						if (property)
						{

						}
						for (xml_node row = sprite.child("Row"); row; row = row.next_sibling("Row"))
						{
						}
					}
				}
			}
		}*/
	}
}