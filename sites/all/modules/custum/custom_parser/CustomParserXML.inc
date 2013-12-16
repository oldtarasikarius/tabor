<?php

/**
 * @file
 * Provides the XML import feeds parser plugin.
 */

/**
 * Parses a given file as a XML file.
 */
class CustomParserXML extends FeedsParser {

  /**
   * Implements FeedsParser::parse().
   */
  public function parse(FeedsSource $source, FeedsFetcherResult $fetcher_result) {
    @ $xml = simplexml_load_string($fetcher_result->getRaw(), NULL, LIBXML_NOERROR | LIBXML_NOWARNING | LIBXML_NOCDATA);
    // Got a malformed XML.
    if ($xml === FALSE || is_null($xml)) {
      return FALSE;
    }
    $items = array();
    foreach ($xml->node as $node) {
      $node = (array) $node;
      foreach ($node as $k => $v) {
        if (!$v) {
          unset($node[$k]);
        }
        else {
          $old_key = $k;
          $new_key = drupal_strtolower(str_replace('-', ' ', $old_key));
          $node[$new_key] = $v;
          unset($node[$old_key]);
        }
      }
      $items[] = $node;
    }
    return new FeedsParserResult($items, $source->feed_nid);
  }

  /**
   * Override parent::getSourceElement() to use only lower keys.
   */
  public function getSourceElement(FeedsSource $source, FeedsParserResult $result, $element_key) {
    return parent::getSourceElement($source, $result, drupal_strtolower($element_key));
  }
}
