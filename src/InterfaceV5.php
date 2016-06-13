<?php

namespace Drupal\cleverreach;

/**
 * InterfaceV5
 * @author WSDLInterpreter
 */
class InterfaceV5 extends \SoapClient {
  /**
   * Constructor using wsdl location and options array
   * @param string $wsdl WSDL location for this service
   * @param array $options Options for the SoapClient
   */
  public function __construct($wsdl="http://api.cleverreach.com/soap/interface_v5.1.php?wsdl", $options=array()) {
    parent::__construct($wsdl, $options);
  }

  /**
   * Service Call: clientGetDetails
   *
   * @param string $apiKey
   *
   * @return \Drupal\cleverreach\Types\returnClient
   *
   * @throws \Exception invalid function signature message
   */
  public function clientGetDetails($apiKey) {
    $args = func_get_args();
    return $this->__soapCall("clientGetDetails", $args);
  }


  /**
   * Service Call: clientRegisterMyProductSearch
   *
   * @param string $apiKey
   * @param string $name
   * @param string $url
   * @param string $password
   *
   * @return \Drupal\cleverreach\Types\returnString
   *
   * @throws \Exception invalid function signature message
   */
  public function clientRegisterMyProductSearch($apiKey, $name, $url, $password) {
    $args = func_get_args();
    return $this->__soapCall("clientRegisterMyProductSearch", $args);
  }


  /**
   * Service Call: ClientGlobalBlacklistAdd
   *
   * @param string $apiKey
   * @param string $email
   *
   * @return \Drupal\cleverreach\Types\returnString
   *
   * @throws \Exception invalid function signature message
   */
  public function ClientGlobalBlacklistAdd($apiKey, $email) {
    $args = func_get_args();
    return $this->__soapCall("ClientGlobalBlacklistAdd", $args);
  }


  /**
   * Service Call: ClientGlobalBlacklistRemove
   *
   * @param string $apiKey
   * @param string $email
   *
   * @return \Drupal\cleverreach\Types\returnString
   *
   * @throws \Exception invalid function signature message
   */
  public function ClientGlobalBlacklistRemove($apiKey, $email) {
    $args = func_get_args();
    return $this->__soapCall("ClientGlobalBlacklistRemove", $args);
  }


  /**
   * Service Call: tradeTokenForApiKey
   *
   * @param string $token
   *
   * @return \Drupal\cleverreach\Types\returnString
   *
   * @throws \Exception invalid function signature message
   */
  public function tradeTokenForApiKey($token) {
    $args = func_get_args();
    return $this->__soapCall("tradeTokenForApiKey", $args);
  }


  /**
   * Service Call: receiverAdd
   *
   * @param string $apiKey
   * @param integer $listId
   * @param \Drupal\cleverreach\Types\receiverData $subscriberData
   *
   * @return \Drupal\cleverreach\Types\returnReceiver
   *
   * @throws \Exception invalid function signature message
   */
  public function receiverAdd($apiKey, $listId, \Drupal\cleverreach\Types\receiverData $subscriberData) {
    $args = func_get_args();
    return $this->__soapCall("receiverAdd", $args);
  }


  /**
   * Service Call: receiverAddBatch
   *
   * @param string $apiKey
   * @param integer $listId
   * @param \Drupal\cleverreach\Types\receiverBatchList $subscriberData
   *
   * @return \Drupal\cleverreach\Types\returnString
   *
   * @throws \Exception invalid function signature message
   */
  public function receiverAddBatch($apiKey, $listId, \Drupal\cleverreach\Types\receiverBatchList $subscriberData) {
    $args = func_get_args();
    return $this->__soapCall("receiverAddBatch", $args);
  }


  /**
   * Service Call: receiverUpdate
   *
   * @param string $apiKey
   * @param integer $listId
   * @param \Drupal\cleverreach\Types\receiverData $userData
   *
   * @return \Drupal\cleverreach\Types\returnReceiver
   *
   * @throws \Exception invalid function signature message
   */
  public function receiverUpdate($apiKey, $listId, \Drupal\cleverreach\Types\receiverData $userData) {
    $args = func_get_args();
    return $this->__soapCall("receiverUpdate", $args);
  }


  /**
   * Service Call: receiverUpdateBatch
   *
   * @param string $apiKey
   * @param integer $listId
   * @param \Drupal\cleverreach\Types\receiverBatchList $userData
   *
   * @return \Drupal\cleverreach\Types\returnString
   *
   * @throws \Exception invalid function signature message
   */
  public function receiverUpdateBatch($apiKey, $listId, \Drupal\cleverreach\Types\receiverBatchList $userData) {
    $args = func_get_args();
    return $this->__soapCall("receiverUpdateBatch", $args);
  }


  /**
   * Service Call: receiverDelete
   *
   * @param string $apiKey
   * @param integer $listId
   * @param string $email
   *
   * @return \Drupal\cleverreach\Types\returnString
   *
   * @throws \Exception invalid function signature message
   */
  public function receiverDelete($apiKey, $listId, $email) {
    $args = func_get_args();
    return $this->__soapCall("receiverDelete", $args);
  }


  /**
   * Service Call: receiverSetActive
   *
   * @param string $apiKey
   * @param integer $listId
   * @param string $email
   *
   * @return \Drupal\cleverreach\Types\returnReceiver
   *
   * @throws \Exception invalid function signature message
   */
  public function receiverSetActive($apiKey, $listId, $email) {
    $args = func_get_args();
    return $this->__soapCall("receiverSetActive", $args);
  }


  /**
   * Service Call: receiverSetInactive
   *
   * @param string $apiKey
   * @param integer $listId
   * @param string $email
   *
   * @return \Drupal\cleverreach\Types\returnReceiver
   *
   * @throws \Exception invalid function signature message
   */
  public function receiverSetInactive($apiKey, $listId, $email) {
    $args = func_get_args();
    return $this->__soapCall("receiverSetInactive", $args);
  }


  /**
   * Service Call: receiverGetByEmail
   *
   * @param string $apiKey
   * @param integer $listId
   * @param string $email
   * @param integer $level
   *
   * @return \Drupal\cleverreach\Types\returnReceiver
   *
   * @throws \Exception invalid function signature message
   */
  public function receiverGetByEmail($apiKey, $listId, $email, $level) {
    $args = func_get_args();
    return $this->__soapCall("receiverGetByEmail", $args);
  }


  /**
   * Service Call: receiverGetById
   *
   * @param string $apiKey
   * @param integer $listId
   * @param integer $id
   * @param integer $level
   *
   * @return \Drupal\cleverreach\Types\returnReceiver
   *
   * @throws \Exception invalid function signature message
   */
  public function receiverGetById($apiKey, $listId, $id, $level) {
    $args = func_get_args();
    return $this->__soapCall("receiverGetById", $args);
  }


  /**
   * Service Call: receiverGetPage
   *
   * @param string $apiKey
   * @param integer $listId
   * @param \Drupal\cleverreach\Types\pageFilterSegment $page
   *
   * @return \Drupal\cleverreach\Types\returnReceivers
   *
   * @throws \Exception invalid function signature message
   */
  public function receiverGetPage($apiKey, $listId, \Drupal\cleverreach\Types\pageFilterSegment $page) {
    $args = func_get_args();
    return $this->__soapCall("receiverGetPage", $args);
  }


  /**
   * Service Call: receiverGetByDate
   *
   * @param string $apiKey
   * @param integer $listId
   * @param \Drupal\cleverreach\Types\dateFilterSegment $page
   *
   * @return \Drupal\cleverreach\Types\returnReceivers
   *
   * @throws \Exception invalid function signature message
   */
  public function receiverGetByDate($apiKey, $listId, \Drupal\cleverreach\Types\dateFilterSegment $page) {
    $args = func_get_args();
    return $this->__soapCall("receiverGetByDate", $args);
  }


  /**
   * Service Call: receiverAddOrder
   *
   * @param string $apiKey
   * @param integer $listId
   * @param string $email
   * @param \Drupal\cleverreach\Types\receiverOrder $orderData
   *
   * @return \Drupal\cleverreach\Types\returnString
   *
   * @throws \Exception invalid function signature message
   */
  public function receiverAddOrder($apiKey, $listId, $email, \Drupal\cleverreach\Types\receiverOrder $orderData) {
    $args = func_get_args();
    return $this->__soapCall("receiverAddOrder", $args);
  }


  /**
   * Service Call: receiverAddOrderBatch
   *
   * @param string $apiKey
   * @param integer $listId
   * @param \Drupal\cleverreach\Types\receiverOrderBatch $orderList
   *
   * @return \Drupal\cleverreach\Types\returnString
   *
   * @throws \Exception invalid function signature message
   */
  public function receiverAddOrderBatch($apiKey, $listId, \Drupal\cleverreach\Types\receiverOrderBatch $orderList) {
    $args = func_get_args();
    return $this->__soapCall("receiverAddOrderBatch", $args);
  }


  /**
   * Service Call: groupAdd
   *
   * @param string $apiKey
   * @param string $name
   *
   * @return \Drupal\cleverreach\Types\returnGroup
   *
   * @throws \Exception invalid function signature message
   */
  public function groupAdd($apiKey, $name) {
    $args = func_get_args();
    return $this->__soapCall("groupAdd", $args);
  }


  /**
   * Service Call: groupDelete
   *
   * @param string $apiKey
   * @param integer $listId
   *
   * @return \Drupal\cleverreach\Types\returnString
   *
   * @throws \Exception invalid function signature message
   */
  public function groupDelete($apiKey, $listId) {
    $args = func_get_args();
    return $this->__soapCall("groupDelete", $args);
  }


  /**
   * Service Call: groupClear
   *
   * @param string $apiKey
   * @param integer $listId
   *
   * @return \Drupal\cleverreach\Types\returnString
   *
   * @throws \Exception invalid function signature message
   */
  public function groupClear($apiKey, $listId) {
    $args = func_get_args();
    return $this->__soapCall("groupClear", $args);
  }


  /**
   * Service Call: groupFilterAdd
   *
   * @param string $apiKey
   * @param integer $listId
   * @param string $name
   * @param \Drupal\cleverreach\Types\filterRules $rules
   *
   * @return \Drupal\cleverreach\Types\returnFilter
   *
   * @throws \Exception invalid function signature message
   */
  public function groupFilterAdd($apiKey, $listId, $name, \Drupal\cleverreach\Types\filterRules $rules) {
    $args = func_get_args();
    return $this->__soapCall("groupFilterAdd", $args);
  }


  /**
   * Service Call: groupGetList
   *
   * @param string $apiKey
   *
   * @return \Drupal\cleverreach\Types\returnGroups
   *
   * @throws \Exception invalid function signature message
   */
  public function groupGetList($apiKey) {
    $args = func_get_args();
    return $this->__soapCall("groupGetList", $args);
  }


  /**
   * Service Call: groupGetStats
   *
   * @param string $apiKey
   * @param integer $listId
   *
   * @return \Drupal\cleverreach\Types\returnStats
   *
   * @throws \Exception invalid function signature message
   */
  public function groupGetStats($apiKey, $listId) {
    $args = func_get_args();
    return $this->__soapCall("groupGetStats", $args);
  }


  /**
   * Service Call: groupCSVImport
   *
   * @param string $apiKey
   * @param integer $listId
   * @param string $file
   * @param string $action
   *
   * @return \Drupal\cleverreach\Types\returnString
   *
   * @throws \Exception invalid function signature message
   */
  public function groupCSVImport($apiKey, $listId, $file, $action) {
    $args = func_get_args();
    return $this->__soapCall("groupCSVImport", $args);
  }


  /**
   * Service Call: groupGetDetails
   *
   * @param string $apiKey
   * @param integer $listId
   *
   * @return \Drupal\cleverreach\Types\returnGroup
   *
   * @throws \Exception invalid function signature message
   */
  public function groupGetDetails($apiKey, $listId) {
    $args = func_get_args();
    return $this->__soapCall("groupGetDetails", $args);
  }


  /**
   * Service Call: groupAttributeAdd
   *
   * @param string $apiKey
   * @param integer $listId
   * @param string $name
   * @param string $type
   * @param string $default
   *
   * @return \Drupal\cleverreach\Types\returnString
   *
   * @throws \Exception invalid function signature message
   */
  public function groupAttributeAdd($apiKey, $listId, $name, $type, $default) {
    $args = func_get_args();
    return $this->__soapCall("groupAttributeAdd", $args);
  }


  /**
   * Service Call: groupAttributeDelete
   *
   * @param string $apiKey
   * @param integer $listId
   * @param string $name
   *
   * @return \Drupal\cleverreach\Types\returnString
   *
   * @throws \Exception invalid function signature message
   */
  public function groupAttributeDelete($apiKey, $listId, $name) {
    $args = func_get_args();
    return $this->__soapCall("groupAttributeDelete", $args);
  }


  /**
   * Service Call: groupBlacklistAdd
   *
   * @param string $apiKey
   * @param integer $listId
   * @param string $email
   *
   * @return \Drupal\cleverreach\Types\returnString
   *
   * @throws \Exception invalid function signature message
   */
  public function groupBlacklistAdd($apiKey, $listId, $email) {
    $args = func_get_args();
    return $this->__soapCall("groupBlacklistAdd", $args);
  }


  /**
   * Service Call: groupBlacklistRemove
   *
   * @param string $apiKey
   * @param integer $listId
   * @param string $email
   *
   * @return \Drupal\cleverreach\Types\returnString
   *
   * @throws \Exception invalid function signature message
   */
  public function groupBlacklistRemove($apiKey, $listId, $email) {
    $args = func_get_args();
    return $this->__soapCall("groupBlacklistRemove", $args);
  }


  /**
   * Service Call: groupUpdateName
   *
   * @param string $apiKey
   * @param integer $groupId
   * @param string $name
   *
   * @return \Drupal\cleverreach\Types\returnGroup
   *
   * @throws \Exception invalid function signature message
   */
  public function groupUpdateName($apiKey, $groupId, $name) {
    $args = func_get_args();
    return $this->__soapCall("groupUpdateName", $args);
  }


  /**
   * Service Call: formsGetList
   *
   * @param string $apiKey
   * @param integer $listId
   *
   * @return \Drupal\cleverreach\Types\returnForms
   *
   * @throws \Exception invalid function signature message
   */
  public function formsGetList($apiKey, $listId) {
    $args = func_get_args();
    return $this->__soapCall("formsGetList", $args);
  }


  /**
   * Service Call: formsGetCode
   *
   * @param string $apiKey
   * @param integer $formId
   * @param boolean $ssl
   * @param boolean $badget
   *
   * @return \Drupal\cleverreach\Types\returnString
   *
   * @throws \Exception invalid function signature message
   */
  public function formsGetCode($apiKey, $formId, $ssl, $badget) {
    $args = func_get_args();
    return $this->__soapCall("formsGetCode", $args);
  }


  /**
   * Service Call: formsGetEmbeddedCode
   *
   * @param string $apiKey
   * @param integer $formId
   * @param boolean $ssl
   * @param boolean $badget
   *
   * @return \Drupal\cleverreach\Types\returnString
   *
   * @throws \Exception invalid function signature message
   */
  public function formsGetEmbeddedCode($apiKey, $formId, $ssl, $badget) {
    $args = func_get_args();
    return $this->__soapCall("formsGetEmbeddedCode", $args);
  }


  /**
   * Service Call: formsActivationMail
   *
   * @param string $apiKey
   * @param integer $formId
   * @param string $email
   *
   * @return \Drupal\cleverreach\Types\returnString
   *
   * @throws \Exception invalid function signature message
   */
  public function formsActivationMail($apiKey, $formId, $email) {
    $args = func_get_args();
    return $this->__soapCall("formsActivationMail", $args);
  }


  /**
   * Service Call: formsSendActivationMail
   *
   * @param string $apiKey
   * @param integer $formId
   * @param string $email
   * @param \Drupal\cleverreach\Types\DOIData $doidata
   *
   * @return \Drupal\cleverreach\Types\returnString
   *
   * @throws \Exception invalid function signature message
   */
  public function formsSendActivationMail($apiKey, $formId, $email, \Drupal\cleverreach\Types\DOIData $doidata) {
    $args = func_get_args();
    return $this->__soapCall("formsSendActivationMail", $args);
  }


  /**
   * Service Call: formsUnsubscribeMail
   *
   * @param string $apiKey
   * @param integer $formId
   * @param string $email
   *
   * @return \Drupal\cleverreach\Types\returnString
   *
   * @throws \Exception invalid function signature message
   */
  public function formsUnsubscribeMail($apiKey, $formId, $email) {
    $args = func_get_args();
    return $this->__soapCall("formsUnsubscribeMail", $args);
  }


  /**
   * Service Call: formsSendUnsubscribeMail
   *
   * @param string $apiKey
   * @param integer $formId
   * @param string $email
   *
   * @return \Drupal\cleverreach\Types\returnString
   *
   * @throws \Exception invalid function signature message
   */
  public function formsSendUnsubscribeMail($apiKey, $formId, $email) {
    $args = func_get_args();
    return $this->__soapCall("formsSendUnsubscribeMail", $args);
  }


  /**
   * Service Call: mailingCreate
   *
   * @param string $apiKey
   * @param \Drupal\cleverreach\Types\mailingData $mailingData
   *
   * @return \Drupal\cleverreach\Types\returnMailing
   *
   * @throws \Exception invalid function signature message
   */
  public function mailingCreate($apiKey, \Drupal\cleverreach\Types\mailingData $mailingData) {
    $args = func_get_args();
    return $this->__soapCall("mailingCreate", $args);
  }


  /**
   * Service Call: mailingUpdate
   *
   * @param string $apiKey
   * @param integer $mailingId
   * @param \Drupal\cleverreach\Types\mailingData $mailingData
   *
   * @return \Drupal\cleverreach\Types\returnMailing
   *
   * @throws \Exception invalid function signature message
   */
  public function mailingUpdate($apiKey, $mailingId, \Drupal\cleverreach\Types\mailingData $mailingData) {
    $args = func_get_args();
    return $this->__soapCall("mailingUpdate", $args);
  }


  /**
   * Service Call: mailingGet
   *
   * @param string $apiKey
   * @param integer $mailingId
   *
   * @return \Drupal\cleverreach\Types\returnMailing
   *
   * @throws \Exception invalid function signature message
   */
  public function mailingGet($apiKey, $mailingId) {
    $args = func_get_args();
    return $this->__soapCall("mailingGet", $args);
  }


  /**
   * Service Call: mailingAddgroup
   *
   * @param string $apiKey
   * @param integer $mailingId
   * @param integer $GroupId
   *
   * @return \Drupal\cleverreach\Types\returnMailing
   *
   * @throws \Exception invalid function signature message
   */
  public function mailingAddgroup($apiKey, $mailingId, $GroupId) {
    $args = func_get_args();
    return $this->__soapCall("mailingAddgroup", $args);
  }


  /**
   * Service Call: reportGetList
   *
   * @param string $apiKey
   *
   * @return \Drupal\cleverreach\Types\returnReports
   *
   * @throws \Exception invalid function signature message
   */
  public function reportGetList($apiKey) {
    $args = func_get_args();
    return $this->__soapCall("reportGetList", $args);
  }


  /**
   * Service Call: reportGetDetailedList
   *
   * @param string $apiKey
   *
   * @return \Drupal\cleverreach\Types\returnDetailedReports
   *
   * @throws \Exception invalid function signature message
   */
  public function reportGetDetailedList($apiKey) {
    $args = func_get_args();
    return $this->__soapCall("reportGetDetailedList", $args);
  }


  /**
   * Service Call: reportCampaignGetList
   *
   * @param string $apiKey
   *
   * @return \Drupal\cleverreach\Types\returnReports
   *
   * @throws \Exception invalid function signature message
   */
  public function reportCampaignGetList($apiKey) {
    $args = func_get_args();
    return $this->__soapCall("reportCampaignGetList", $args);
  }


  /**
   * Service Call: reportGetDetails
   *
   * @param string $apiKey
   * @param integer $reportId
   * @param integer $level
   *
   * @return \Drupal\cleverreach\Types\returnReport
   *
   * @throws \Exception invalid function signature message
   */
  public function reportGetDetails($apiKey, $reportId, $level) {
    $args = func_get_args();
    return $this->__soapCall("reportGetDetails", $args);
  }


  /**
   * Service Call: reportGetUserActivity
   *
   * @param string $apiKey
   * @param integer $reportId
   * @param \Drupal\cleverreach\Types\dateReportFilterSegment $page
   *
   * @return \Drupal\cleverreach\Types\returnReportReceivers
   *
   * @throws \Exception invalid function signature message
   */
  public function reportGetUserActivity($apiKey, $reportId, \Drupal\cleverreach\Types\dateReportFilterSegment $page) {
    $args = func_get_args();
    return $this->__soapCall("reportGetUserActivity", $args);
  }


}