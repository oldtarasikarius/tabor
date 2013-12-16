<?php
/**
 * A Jay example parser.
 */
class JayParser extends FeedsParser {
/**
 * Implements FeedsParser::parse().
 */
  public function parse(FeedsSource $source, FeedsFetcherResult $fetcher_result) {
    // Load xml-file into string.
    @ $xml = simplexml_load_string($fetcher_result->getRaw(), NULL, LIBXML_NOERROR | LIBXML_NOWARNING);
    if ($xml === FALSE || is_null($xml)) {
      return FALSE;
    }
    $items = array();
    foreach ($xml->node as $node) {
      $node = (array) $node;
      foreach ($node as $k=>$v) {
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
  public function getSourceElement(FeedsSource $source, FeedsParserResult $result, $element_key) {
    return parent::getSourceElement($source, $result, drupal_strtolower($element_key));
  }
}