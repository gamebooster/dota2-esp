
#include "dota_usermessage_helpers.h"

CDotaUsermessageHelpers g_DotaUsermessageHelpers;

#define SETUP_MESSAGE( msgname )                          \
	m_NameIndexMap.Insert( #msgname,  UM_##msgname  ); \
	m_IndexNameMap[UM_##msgname] = #msgname;           \
	m_Prototypes[UM_##msgname] = &CUserMsg_##msgname::default_instance();

#define SETUP_DOTA_MESSAGE( msgname )                          \
	m_NameIndexMap.Insert( #msgname,  DOTA_UM_##msgname  ); \
	m_IndexNameMap[DOTA_UM_##msgname] = #msgname;           \
	m_Prototypes[DOTA_UM_##msgname] = &CDOTAUserMsg_##msgname::default_instance();

#define SETUP_MESSAGE_MANUAL( enum_name, cls_name, msgname )                          \
	m_NameIndexMap.Insert( #msgname,  enum_name  ); \
	m_IndexNameMap[enum_name] = #msgname;           \
	m_Prototypes[enum_name] = &cls_name::default_instance();

CDotaUsermessageHelpers::CDotaUsermessageHelpers()
{
	// Clear all so that any unused are inited.
	memset( m_Prototypes, 0, sizeof(m_Prototypes) );
	memset( m_IndexNameMap, 0, sizeof(m_IndexNameMap) );

	SETUP_MESSAGE( AchievementEvent );
	SETUP_MESSAGE( CloseCaption );
	//SETUP_MESSAGE( CloseCaptionDirect );
	SETUP_MESSAGE( CurrentTimescale );
	SETUP_MESSAGE( DesiredTimescale );
	SETUP_MESSAGE( Fade );
	SETUP_MESSAGE( GameTitle );
	SETUP_MESSAGE( Geiger );
	SETUP_MESSAGE( HintText );
	SETUP_MESSAGE( HudMsg );
	SETUP_MESSAGE( HudText );
	SETUP_MESSAGE( KeyHintText );
	SETUP_MESSAGE( MessageText );
	SETUP_MESSAGE( RequestState );
	SETUP_MESSAGE( ResetHUD );
	SETUP_MESSAGE( Rumble );
	SETUP_MESSAGE( SayText );
	SETUP_MESSAGE( SayText2 );
	SETUP_MESSAGE( SayTextChannel );
	SETUP_MESSAGE( Shake );
	SETUP_MESSAGE( ShakeDir );
	SETUP_MESSAGE( StatsCrawlMsg );
	SETUP_MESSAGE( StatsSkipState );
	SETUP_MESSAGE( TextMsg );
	SETUP_MESSAGE( Tilt );
	SETUP_MESSAGE( Train );
	SETUP_MESSAGE( VGUIMenu );
	SETUP_MESSAGE( VoiceMask );
	SETUP_MESSAGE( VoiceSubtitle );
	SETUP_MESSAGE( SendAudio );

	//SETUP_DOTA_MESSAGE( AddUnitToSelection );
	SETUP_DOTA_MESSAGE( AIDebugLine );
	SETUP_DOTA_MESSAGE( ChatEvent );
	SETUP_DOTA_MESSAGE( CombatHeroPositions );
	SETUP_DOTA_MESSAGE( CombatLogData );
	SETUP_DOTA_MESSAGE( CombatLogShowDeath );
	SETUP_DOTA_MESSAGE( CreateLinearProjectile );
	SETUP_DOTA_MESSAGE( DestroyLinearProjectile );
	SETUP_DOTA_MESSAGE( DodgeTrackingProjectiles );
	SETUP_DOTA_MESSAGE( GlobalLightColor );
	SETUP_DOTA_MESSAGE( GlobalLightDirection );
	SETUP_DOTA_MESSAGE( InvalidCommand );
	SETUP_DOTA_MESSAGE( LocationPing );
	SETUP_DOTA_MESSAGE( MapLine );
	SETUP_DOTA_MESSAGE( MiniKillCamInfo );
	SETUP_DOTA_MESSAGE( MinimapDebugPoint );
	SETUP_DOTA_MESSAGE( MinimapEvent );
	SETUP_DOTA_MESSAGE( NevermoreRequiem );
	SETUP_DOTA_MESSAGE( OverheadEvent );
	SETUP_DOTA_MESSAGE( SetNextAutobuyItem );
	SETUP_DOTA_MESSAGE( SharedCooldown );
	SETUP_DOTA_MESSAGE( SpectatorPlayerClick );
	SETUP_DOTA_MESSAGE( TutorialTipInfo );
	SETUP_DOTA_MESSAGE( UnitEvent );
	SETUP_DOTA_MESSAGE( ParticleManager );
	SETUP_DOTA_MESSAGE( BotChat );
	SETUP_DOTA_MESSAGE( HudError );
	SETUP_DOTA_MESSAGE( ItemPurchased );
	SETUP_DOTA_MESSAGE( Ping );
	SETUP_DOTA_MESSAGE( ItemFound );
	//SETUP_MESSAGE( CharacterSpeakConcept );
	SETUP_DOTA_MESSAGE( SwapVerify );
	SETUP_DOTA_MESSAGE( WorldLine );
	SETUP_DOTA_MESSAGE( TournamentDrop );
	SETUP_DOTA_MESSAGE( ItemAlert );
	SETUP_DOTA_MESSAGE( HalloweenDrops );
	SETUP_DOTA_MESSAGE( ChatWheel );
	SETUP_DOTA_MESSAGE( ReceivedXmasGift );
	SETUP_DOTA_MESSAGE( UpdateSharedContent );
	SETUP_DOTA_MESSAGE( TutorialRequestExp );
	SETUP_DOTA_MESSAGE( TutorialPingMinimap );
	SETUP_MESSAGE_MANUAL( DOTA_UM_GamerulesStateChanged, CDOTA_UM_GamerulesStateChanged, GamerulesStateChanged );
	SETUP_DOTA_MESSAGE( ShowSurvey );
	SETUP_DOTA_MESSAGE( TutorialFade );
	SETUP_DOTA_MESSAGE( AddQuestLogEntry );
	SETUP_DOTA_MESSAGE( SendStatPopup );
	SETUP_DOTA_MESSAGE( TutorialFinish );
	SETUP_DOTA_MESSAGE( SendRoshanPopup );
	SETUP_DOTA_MESSAGE( SendGenericToolTip );
}

const google::protobuf::Message *CDotaUsermessageHelpers::GetPrototype( int index ) const
{
	if( index >= 0 && index < EDotaUserMessages_ARRAYSIZE )
		return m_Prototypes[index];

	return NULL;
}

const google::protobuf::Message *CDotaUsermessageHelpers::GetPrototype( const char *name ) const
{
	int index = GetIndex( name );
	if( index > -1 )
		return m_Prototypes[ index ];

	return NULL;
}

int CDotaUsermessageHelpers::GetIndex( const char *name ) const
{
	int idx = m_NameIndexMap.Find( name );
	if( idx != m_NameIndexMap.InvalidHandle() )
		return m_NameIndexMap[idx];

	return -1;
}

const char *CDotaUsermessageHelpers::GetName( int index ) const
{
	if( index >= 0 && index < EDotaUserMessages_ARRAYSIZE )
		return m_IndexNameMap[index];

	return NULL;
}

